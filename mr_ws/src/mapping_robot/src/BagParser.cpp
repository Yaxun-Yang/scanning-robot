#include "BagParser.h"
#include "JPEGDecoder.h"

namespace stereye {
BagParser::BagParser(ros::NodeHandle &nh): mNh(nh){
    mNh.getParam("jpg_topic", mJpgTopic);
    mNh.getParam("depth_topic", mDepthTopic);
    mNh.getParam("bag_path", mBagPath);
    mNh.getParam("pose_path", mPosePath);
    mNh.getParam("export_path", mExportPath);
    std::string calibrationPath;
    mNh.getParam("calibration_path", calibrationPath);

    mpCam = std::make_shared<Camera>(calibrationPath);
    mpCam->initUndistortRectifyMap();
    mpCamResized = mpCam->rescale(mpCam->scale());
    mpCamResized->initUndistortRectifyMap();
    mpJPEGDecoder = std::make_shared<JPEGDecoder>(mpCam->w(), mpCam->h(), 1, 1);

    mpJpgSub = std::make_shared<BagSubscriber<sensor_msgs::CompressedImage>>();
    mpDepthSub = std::make_shared<BagSubscriber<sensor_msgs::Image>>();
    mpOdomSub = std::make_shared<BagSubscriber<geometry_msgs::PoseStamped>>();
    // Use time synchronizer to make sure we get properly synchronized images
    mpSync = std::make_shared<message_filters::Synchronizer<imageOdomSync>>(
        imageOdomSync(10), *mpJpgSub, *mpDepthSub, *mpOdomSub);
    mpSync->registerCallback(boost::bind(&BagParser::imageOdomCb, this, _1, _2, _3));
    printf("Init BagParser done!\n");
}



std::queue<geometry_msgs::PoseStamped::Ptr> BagParser::loadPoses(const std::string &path) {
    std::queue<geometry_msgs::PoseStamped::Ptr> poses;
    FILE * infile = fopen(path.c_str(), "r");
    if (!infile) {
        printf("Fail to open pose file! Given path: %s\n", path.c_str());
        exit(-1);
    }
    while (true) {
        geometry_msgs::PoseStamped::Ptr pose(new geometry_msgs::PoseStamped);
        double time;
        int num = fscanf(infile, "%lf %lf %lf %lf %lf %lf %lf %lf\n",
                                                        &time,
                                                        &pose->pose.orientation.x, &pose->pose.orientation.y, &pose->pose.orientation.z, &pose->pose.orientation.w,
                                                        &pose->pose.position.x, &pose->pose.position.y, &pose->pose.position.z);
        if (num != 8) break;
        pose->header.stamp = ros::Time().fromSec(time);
        poses.push(pose);
    }
    return poses;
}

cv::Mat compressImage(const cv::Mat& image) {
    std::vector<unsigned char> dataEncoded;
    // Compression settings
    std::vector<int> params(2, 0);
    params[0] = cv::IMWRITE_JPEG_QUALITY;
    params[1] = 90;
    cv::imencode(".jpg", image, dataEncoded, params);
    cv::Mat jpg = cv::Mat(1, dataEncoded.size(), CV_8UC1);
    memcpy(jpg.data, dataEncoded.data(), jpg.cols);
    // std::cout << ".jpg " << dataEncoded.size() << std::endl;
    return jpg;
}

void BagParser::imageOdomCb(const sensor_msgs::CompressedImage::ConstPtr &jpgMsg,
                                                                  const sensor_msgs::ImageConstPtr &depthMsg,
                                                                  const geometry_msgs::PoseStamped::ConstPtr &odomMsg) {
        mProcessing = true;
        std::cout << jpgMsg->header.stamp.toNSec() <<" " << depthMsg->header.stamp.toNSec() <<" " <<odomMsg->header.stamp.toNSec() <<" "<< mId<< std::endl;
        cv::Mat rgb, rgbResized, jpg;
        // uncompress jpg message, with distortion
        // cuda decoder, todo: add try catch
        {
            char *dist = mpJPEGDecoder->process(jpgMsg->data.data(),  jpgMsg->data.size());
            rgb = cv::Mat(mpCam->h(), mpCam->w(), CV_8UC3, dist);
        }
        // cpu decode
        // jpg = cv::Mat(1, jpgMsg->data.size(), CV_8UC1);
        // memcpy(jpg.data, jpgMsg->data.data(), jpg.cols);
        // rgb = cv::imdecode(jpg, cv::IMREAD_UNCHANGED);
        // // uncompressImage(jpgMsg, mpJPEGDecoder, rgb);
        // // undistortion
        rgb = mpCam->undistortImage(rgb);
        // compress to save, no distortion
        // jpg = compressImage(rgb);
        cv::resize(rgb, rgbResized, cv::Size(mpCamResized->w(), mpCamResized->h()), 0, 0, cv::INTER_AREA);

        cv_bridge::CvImagePtr depthPtr = cv_bridge::toCvCopy(depthMsg, sensor_msgs::image_encodings::TYPE_16UC1);
        cv::Mat depth = mpCamResized->undistortDepth(depthPtr->image);

        // process odom
        Eigen::Affine3d odom;
	    tf::poseMsgToEigen(odomMsg->pose, odom);

        cv::imwrite(mExportPath+"/rgb/"+std::to_string(mId)+".jpg", rgbResized);
        cv::imwrite(mExportPath+"/depth/"+std::to_string(mId)+".png", depth);
        fprintf(mpOutPoses, "%d %d\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n", mId, mId,
                    odom(0,0), odom(0,1), odom(0,2), odom(0,3),
                    odom(1,0), odom(1,1), odom(1,2), odom(1,3),
                    odom(2,0), odom(2,1), odom(2,2), odom(2,3));

        // std::cout << "Write data:"<< id << " done!"<<std::endl;
        ++mId;
        mProcessing = false;
}

void BagParser::start() {
    std::queue<geometry_msgs::PoseStamped::Ptr> poses = loadPoses(mPosePath);
    utils::mkdirs(mExportPath);
    utils::mkdirs(mExportPath+"/rgb");
    utils::mkdirs(mExportPath+"/depth");
    mpOutPoses = fopen((mExportPath+"/poses.txt").c_str(), "w");
    mpCam->writeConfig(mExportPath+"/calibration.txt");

    rosbag::Bag bag;
    bag.open(mBagPath, rosbag::bagmode::Read);
    // Specify topics we need
    std::vector<std::string> topics;
    topics.push_back(mJpgTopic);
    topics.push_back(mDepthTopic);
    ros::Time lastImageStamp = ros::Time().fromSec(0);
    rosbag::View views(bag, rosbag::TopicQuery(topics));
    // Traverse all filtered message, send to message filter
    for (rosbag::MessageInstance const m : views) {
        if (!ros::ok()) break;
        while (mProcessing) {
            usleep(5000);
        }
        if (m.getTopic() == mJpgTopic) {
            sensor_msgs::CompressedImage::Ptr jpgMsg =
                m.instantiate<sensor_msgs::CompressedImage>();
            mpJpgSub->newMessage(jpgMsg);
            lastImageStamp = jpgMsg->header.stamp;
        }
        else if (m.getTopic() == mDepthTopic) {
            sensor_msgs::Image::Ptr depthMsg = m.instantiate<sensor_msgs::Image>();
            mpDepthSub->newMessage(depthMsg);
        }
        // control odom rate
        while (poses.size() && lastImageStamp > ros::Time().fromSec(0) && poses.front()->header.stamp <= lastImageStamp) {
            mpOdomSub->newMessage(poses.front());
            poses.pop();
        }
    }
    bag.close();
    fclose(mpOutPoses);
}

} // namespace stereye