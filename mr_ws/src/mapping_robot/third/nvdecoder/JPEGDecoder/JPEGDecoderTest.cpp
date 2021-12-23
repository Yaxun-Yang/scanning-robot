#include "JPEGDecoder.h"
#include <fstream>
#include <malloc.h>
#include <iostream>
#include <opencv2/opencv.hpp>

uint64_t
get_file_size(std::ifstream * stream)
{
    uint64_t size = 0;
    std::streampos current_pos = stream->tellg();
    stream->seekg(0, stream->end);
    size = stream->tellg();
    stream->seekg(current_pos, stream->beg);
    return size;
}


int main(int argc, char *argv[])
{
  // log_level = 0;
  // read input image data
  unsigned char *src;
  std::ifstream in(argv[1]);
  int in_file_size = get_file_size(&in);
  std::cout << "in_file_size:" << in_file_size << std::endl;
  src = new unsigned char[in_file_size];
  in.read((char*)src, in_file_size);

  // init decoder
  JPEGDecoder decoder(4096,3072);
  char *dist;

//   // timer
//   struct timeval start;
//   struct timeval end;

//   gettimeofday(&start,NULL);
  int count = 1;
  for (int i = 0; i < count; ++i)
    dist = decoder.process(src, in_file_size);

//   gettimeofday(&end,NULL);

//   float time_use = (end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec)/ 1000000.0;//s
//   printf("time_use is %.10f\n",time_use/count);
    cv::Mat bgr = cv::Mat(3072/8, 4096/8, CV_8UC3, dist);
    cv::imwrite(argv[2], bgr);

  return 0;
}
