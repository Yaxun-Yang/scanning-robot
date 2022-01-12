#include "BagParser.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "recorder_node");
    ros::NodeHandle nh("~");
    auto mpParser = std::make_shared<stereye::BagParser>(nh);
    mpParser->start();
    return 0;
}