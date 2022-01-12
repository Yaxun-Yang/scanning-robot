#include "JPEGDecoder.h"

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>

#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/Image.h>

class DecoderWrapper {
public:
    DecoderWrapper(ros::NodeHandle& n, int w, int h, int s,
                                         std::string& jpg_topic, std::string& bgr_topic);

private:
    void jpg_cb(const sensor_msgs::CompressedImage::Ptr &msg);

    ros::Publisher image_pub_;
    ros::Subscriber jpg_sub_;

    JPEGDecoder* decoder_;
    int w_; // scaled w
    int h_; // scaled h
    int s_; // scaled factor
};

DecoderWrapper::DecoderWrapper(ros::NodeHandle& n, int w, int h, int s,
                                                                          std::string& jpg_topic, std::string& bgr_topic) {
    w_ = w / s;
    h_ = h / s;
    decoder_ = new JPEGDecoder(w, h, 1, s);

    jpg_sub_ = n.subscribe(jpg_topic, 1, &DecoderWrapper::jpg_cb, this);
    image_pub_ = n.advertise<sensor_msgs::Image>(bgr_topic, 1);
}

void DecoderWrapper::jpg_cb(const sensor_msgs::CompressedImage::Ptr &msg) {
    // varification: ffmpeg -y -s 512x384 -pix_fmt yuvj422p -i /home/stereye/out.yuv /home/stereye/out.png
    char *res = decoder_->process(msg->data.data(), msg->data.size());
    cv::Mat bgr = cv::Mat(h_, w_, CV_8UC3, res);
    sensor_msgs::ImagePtr image = 
        cv_bridge::CvImage(msg->header, sensor_msgs::image_encodings::BGR8, bgr).toImageMsg();
    image_pub_.publish(image);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "nvdecoder_node");
    ros::NodeHandle n("~");
    // default param
    std::string jpg_topic = "/rgb/image_raw/compressed";
    std::string bgr_topic = "/rgb/image_view";
    int width = 4096, height = 3072, scale = 8;
    // overwrite param
    n.param("jpg_topic", jpg_topic, jpg_topic);
    n.param("bgr_topic", bgr_topic, bgr_topic);
    n.param("width", width, width);
    n.param("height", height, height);
    n.param("scale", scale, scale);

    DecoderWrapper decoder_wrapper(n, width, height, scale, jpg_topic, bgr_topic);
    ros::spin();

    ros::shutdown();
    return 0;
}
