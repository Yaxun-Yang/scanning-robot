#pragma once
#include <ros/ros.h>
#include <rosbag/view.h>
#include <rosbag/bag.h>
#include <tf/tf.h>
#include <eigen_conversions/eigen_msg.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/image_encodings.h>
#include <geometry_msgs/PoseStamped.h>
#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <cv_bridge/cv_bridge.h>
#include <atomic>
#include "Utils.h"
#include "Camera.h"

class JPEGDecoder;

namespace stereye {
typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::CompressedImage, sensor_msgs::Image, geometry_msgs::PoseStamped> imageOdomSync;

template <class M>
class BagSubscriber : public message_filters::SimpleFilter<M> {
public:
    void newMessage(const boost::shared_ptr<M const> &msg) {
        this->signalMessage(msg);
    }
};

class BagParser {
public:
    BagParser(ros::NodeHandle &nh);
    void start();

private:
    std::queue<geometry_msgs::PoseStamped::Ptr> loadPoses(const std::string &path);
    void imageOdomCb(const sensor_msgs::CompressedImage::ConstPtr &jpgMsg,
                                               const sensor_msgs::ImageConstPtr &depthMsg,
                                               const geometry_msgs::PoseStamped::ConstPtr &odomMsg);

    ros::NodeHandle mNh;
    std::shared_ptr<BagSubscriber<sensor_msgs::CompressedImage>> mpJpgSub;
    std::shared_ptr<BagSubscriber<sensor_msgs::Image>> mpDepthSub;
    std::shared_ptr<BagSubscriber<geometry_msgs::PoseStamped>> mpOdomSub;
    std::shared_ptr<message_filters::Synchronizer<imageOdomSync>> mpSync;
    std::string mBagPath, mPosePath, mExportPath;
    std::string mJpgTopic, mDepthTopic;
    
    std::shared_ptr<Camera> mpCam, mpCamResized;
    std::shared_ptr<JPEGDecoder> mpJPEGDecoder;
    unsigned int mId = 0;
    std::atomic<bool> mProcessing;
    FILE *mpOutPoses;
    bool mSave2k=false;
};

} // namespace stereye