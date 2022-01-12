#pragma once

class JPEGDecoderHelper;

class JPEGDecoder {
public:
    JPEGDecoder(int width=4096, int height=3072, int num=1, int denom=8);
    ~JPEGDecoder();

    char *process(unsigned char *data, int data_len);
    char *process(const unsigned char *data, int data_len);

private:
    char *result_bgr_;
    int in_w_, in_h_, out_w_, out_h_;
    int out_len_;
    int num_, denom_;

#ifdef STEREYE_PC
    JPEGDecoderHelper* helper_;
    int in_w_len_, out_w_len_;
#else
    int uv_w_, uv_h_, uv_len_;
    char *yuv422p2bgr();
    char *result_yuv_;
#endif
};
