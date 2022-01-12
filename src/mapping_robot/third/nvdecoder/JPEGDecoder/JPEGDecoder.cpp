#include "JPEGDecoder.h"

#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <sys/time.h>

#ifdef STEREYE_PC
#include <nvjpeg.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <npp.h>

class JPEGDecoderHelper{
private:
    friend class JPEGDecoder;
    // jpeg decode
    nvjpegJpegState_t state_;
    nvjpegHandle_t handle_;
    cudaStream_t stream_;

    // for decode
    nvjpegImage_t result_;

    // nppi resize
    NppiSize in_size_, out_size_;
    NppiRect in_rect_, out_rect_;
    void *in_img_, *out_img_;
};

#else
#include "jpeglib.h"
#endif

JPEGDecoder::JPEGDecoder(int width, int height, int num, int denom) {
    in_w_ = width;
    in_h_ = height;
    out_w_ = width * num / denom;
    out_h_ = height * num / denom;
    out_len_ = out_w_ * out_h_;
    result_bgr_ = new char[out_len_ * 3];
    num_ = num;
    denom_ = denom;

#ifdef STEREYE_PC
    // prepare param for bgr out (decode) 
    helper_ = new JPEGDecoderHelper();
    nvjpegCreateSimple(&helper_->handle_);
    nvjpegJpegStateCreate(helper_->handle_, &helper_->state_);
    cudaStreamCreateWithFlags(&helper_->stream_, cudaStreamNonBlocking);
    in_w_len_ = in_w_ * 3;
    out_w_len_ = out_w_ * 3;
    helper_->result_.pitch[0] = in_w_len_;
    cudaMalloc((void**)&helper_->result_.channel[0], in_w_ * in_h_ * 3);
    // prepare param for bgr out (resize) 
    helper_->in_size_.width = in_w_;
    helper_->in_size_.height = in_h_;
    helper_->out_size_.width = out_w_;
    helper_->out_size_.height = out_h_;
    helper_->in_rect_ = {0, 0, in_w_, in_h_};
    helper_->out_rect_ = {0, 0, out_w_, out_h_};
    int step;
    helper_->in_img_ = nppiMalloc_8u_C3(in_w_, in_h_, &step);
    helper_->out_img_ = nppiMalloc_8u_C3(out_w_, out_h_, &step);
#else
    // prepare param for yuv out
    uv_w_ = out_w_ / 2;
    uv_h_ = out_h_;
    // bytes of data per channel
    uv_len_ = uv_w_ * uv_h_;
    result_yuv_ = new char[out_len_ * 2];
#endif
}

JPEGDecoder::~JPEGDecoder() {
    delete result_bgr_;
#ifdef STEREYE_PC
    nppiFree(helper_->in_img_);
    nppiFree(helper_->out_img_);
    if (helper_->result_.channel[0]) cudaFree(helper_->result_.channel[0]);
    nvjpegJpegStateDestroy(helper_->state_);
    nvjpegDestroy(helper_->handle_);
#else
    delete result_yuv_;
#endif
}

char *JPEGDecoder::process(unsigned char *data, int data_len) {
    return process((const unsigned char *)data, data_len);
}

char *JPEGDecoder::process(const unsigned char *data, int data_len) {
    struct  timeval start;
    struct  timeval end;
    float duration;
    gettimeofday(&start,NULL);
#ifdef STEREYE_PC
    nvjpegDecode(helper_->handle_, helper_->state_, data, data_len,
                                    NVJPEG_OUTPUT_BGRI, &helper_->result_, helper_->stream_);
    cudaStreamSynchronize(helper_->stream_);
    // copy cuda to nppi cuda
    cudaMemcpy2D(helper_->in_img_, in_w_len_, helper_->result_.channel[0],
                                       in_w_len_, in_w_len_, in_h_, cudaMemcpyDeviceToDevice);
    if (num_ == denom_) {
        cudaMemcpy2D((unsigned char *)result_bgr_, out_w_len_, helper_->in_img_, out_w_len_, out_w_len_, out_h_, cudaMemcpyDeviceToHost);
    } else {
        // nppi resize
        //https://docs.nvidia.com/cuda/npp/group__typedefs__npp.html#gga2b58ebd329141d560aa4367f1708f191a5d8f0655f4e2810e3e288cab463dcd46
        nppiResize_8u_C3R((Npp8u *)helper_->in_img_, in_w_len_, helper_->in_size_, helper_->in_rect_,
                            (Npp8u *)helper_->out_img_, out_w_len_, helper_->out_size_, helper_->out_rect_, NPPI_INTER_SUPER);
        cudaDeviceSynchronize();
        // nppi cuda to host
        cudaMemcpy2D((unsigned char *)result_bgr_, out_w_len_, helper_->out_img_, out_w_len_, out_w_len_, out_h_, cudaMemcpyDeviceToHost);
    }
    cudaDeviceSynchronize();
    cudaGetLastError();
#else
    unsigned char*y[4 * DCTSIZE] = {NULL, };
    unsigned char*u[4 * DCTSIZE] = {NULL, };
    unsigned char*v[4 * DCTSIZE] = {NULL, };
    unsigned char**lines[3] = {y, u, v};
    int v_samp[3];
    unsigned char *base[3], *last[3];
    // How many bytes per row of Y, U, and V data.
    const int stride[3] = {out_w_, uv_w_, uv_w_};


    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr err;

    cinfo.err = jpeg_std_error(&err);
    jpeg_create_decompress(&cinfo);
    //reinterpret_cast<unsigned char*>(jpg_buffer.data())
    jpeg_mem_src(&cinfo, const_cast<unsigned char *>(data), data_len);
    jpeg_read_header(&cinfo, true);
    // some settings are changed within jpeg_read_header()
    cinfo.do_fancy_upsampling = FALSE;
    cinfo.do_block_smoothing = FALSE;
    cinfo.out_color_space = cinfo.jpeg_color_space;
    cinfo.dct_method = JDCT_FASTEST;
    cinfo.bMeasure_ImageProcessTime = FALSE;
    cinfo.raw_data_out = TRUE;
    cinfo.scale_num = num_;
    cinfo.scale_denom = denom_;
    jpeg_start_decompress(&cinfo);

    v_samp[0] = cinfo.comp_info[0].v_samp_factor;
    v_samp[1] = cinfo.comp_info[1].v_samp_factor;
    v_samp[2] = cinfo.comp_info[2].v_samp_factor;

    // Starting positions of the Y, U, and V components in the output_buffer
    base[0] = (unsigned char *)result_yuv_; // Y
    base[1] = base[0] + out_len_;         // U
    base[2] = base[1] + uv_len_;        // V

    for (int i = 0; i < out_h_; i += v_samp[0] * DCTSIZE) { 
        for (int j = 0; j < (v_samp[0] * DCTSIZE); j++) {
            lines[0][j] = base[0] + (i + j) * stride[0];
            lines[1][j] = base[1] + (i + j) * stride[1];
            lines[2][j] = base[2] + (i + j) * stride[2];
        }
        jpeg_read_raw_data(&cinfo, lines, v_samp[0] * DCTSIZE);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    // yuv422p to bgr
    yuv422p2bgr();
#endif
    gettimeofday(&end,NULL);
    duration = end.tv_sec-start.tv_sec + (end.tv_usec-start.tv_usec)/1000000.0;
    printf("process takse %fs\n", duration);

    return result_bgr_;
}

inline void yuv2bgr_pixel(int y, int u, int v, unsigned char *pos)
{
    int r, g, b;
    r = y + (1.370705 * (v-128));
    g = y - (0.698001 * (v-128)) - (0.337633 * (u-128));
    b = y + (1.732446 * (u-128));
    if(r > 255) r = 255;
    if(g > 255) g = 255;
    if(b > 255) b = 255;
    if(r < 0) r = 0;
    if(g < 0) g = 0;
    if(b < 0) b = 0;
    pos[0] = b ;
    pos[1] = g ;
    pos[2] = r ;
}

#ifndef STEREYE_PC
char *JPEGDecoder::yuv422p2bgr() {
    int y0, u, y1, v;
    for (int i = 0; i < uv_len_; ++i) {
        y0 = result_yuv_[2*i];
        y1 = result_yuv_[2*i+1];
        u = result_yuv_[out_len_+i];
        v = result_yuv_[out_len_+uv_len_+i];
        yuv2bgr_pixel(y0, u, v, (unsigned char *)result_bgr_+6*i);
        yuv2bgr_pixel(y1, u, v, (unsigned char *)result_bgr_+6*i+3);
    }
    return result_bgr_;
}
#endif
