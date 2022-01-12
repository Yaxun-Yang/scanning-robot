#include "BagRecorder.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "recorder_node");
    ros::NodeHandle nh("~");
    auto mpRecorder = std::make_shared<stereye::BagRecorder>(nh);
    mpRecorder->start();
    return 0;
}