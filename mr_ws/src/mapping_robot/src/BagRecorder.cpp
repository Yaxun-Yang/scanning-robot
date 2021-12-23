#include "BagRecorder.h"
namespace stereye {
using namespace rosbag;

BagRecorder::BagRecorder(ros::NodeHandle &nh): mNh(nh) {
    // get param
    int compression;
    mNh.getParam("compression", compression);
    std::vector<std::string> topics;
    mNh.getParam("topics", topics);
    std::string bagPath;
    mNh.getParam("bag_path", bagPath);
    // setup rosbag::Recorder
    mOpts = RecorderOptions();
    if (!topics.size()) mOpts.record_all = true;
    //   0:Uncompressed    1: BZ2   2: LZ4
    mOpts.compression = compression::CompressionType(int(compression));
    mOpts.topics = topics;
    if (bagPath != "") {
        mOpts.append_date = false;
        mOpts.prefix = bagPath;
    }
    mpRecorder = std::make_shared<rosbag::Recorder>(mOpts);
    // setup service (used to stop recorder)
    mServer = mNh.advertiseService("trigger_stop", &BagRecorder::triggerStop, this);
}

BagRecorder::~BagRecorder() {
}

int BagRecorder::start() {
    return mpRecorder->run();
}

bool BagRecorder::triggerStop(std_srvs::Trigger::Request  &, std_srvs::Trigger::Response &res) {
    // stop
    std::cout << "triggerStop" << std::endl;
    ros::shutdown();
    res.success = true;
    return true;
}

} // namespace stereye