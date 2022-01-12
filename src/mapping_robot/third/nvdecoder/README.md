# NVDecoder

Decode jpeg to rgb on both tegra(yuv422p) and pc(any jpeg) using nvjpeg

Usage: roslaunch jpegdecoder decode.launch

# C++ API

In CMakeLists.txt: `add_subdirectory(nvdecoder/JPEGDecoder)`

Create: `auto mpJPEGDecoder = std::make_shared<JPEGDecoder>(width, height, 1, scale);`

Decode:  `char *data = mpJPEGDecoder->process(jpg.data(),  jpg.size());`

To cv::Mat: `cv::Mat rgb(height/scale, width/scale, CV_8UC3, data);`

Output size will be: (width/scale, height/scale)
