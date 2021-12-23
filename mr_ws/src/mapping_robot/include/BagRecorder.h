#pragma once
#include <ros/ros.h>
#include <rosbag/recorder.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/LaserScan.h>
#include <std_srvs/Trigger.h>

namespace stereye {

class BagRecorder {
public:
    BagRecorder(ros::NodeHandle &nh);
    ~BagRecorder();
    int start();

private:
    bool triggerStop(std_srvs::Trigger::Request  &, std_srvs::Trigger::Response &res);

    std::shared_ptr<rosbag::Recorder> mpRecorder;
    rosbag::RecorderOptions mOpts;

    ros::ServiceServer mServer;
    ros::NodeHandle mNh;
};

} // namespace stereye