#pragma once
#include <eigen3/Eigen/Core>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <memory>

namespace stereye {

class Camera {

public:
    Camera();
    Camera(const std::string &path);

    enum CameraModel
    {
        PINHOLE,// todo: depth?
        FISHEYE
    };
    // load config from yaml(cvfilestorage)
    void init(const std::string& path);
    // simply copy params
    void init(CameraModel model, int w, int h, const cv::Mat &intrinsic,
                      const cv::Mat &distortion, const cv::Mat &extrinsic=cv::Mat::eye(4, 4, CV_64FC1));
    std::shared_ptr<Camera> rescale(int scale);
    void writeConfig(const std::string &path);

    // undistortion, use rectify map anyway, init map after readconfig
    cv::Mat undistortImage(const cv::Mat &input, int flag=cv::INTER_LINEAR);
    cv::Mat undistortDepth(const cv::Mat &input);
    void initUndistortRectifyMap(const cv::Mat &newCameraMatrix=cv::Mat());

    // get params
    const int w() {return mW;}
    const int h() {return mH;}
    double fx() {return mFx;}
    double fy() {return mFy;}
    double cx() {return mCx;}
    double cy() {return mCy;}
    int scale() {return mScale;}
    const cv::Mat &intrinsic() {return mIntrinsic;}
    const cv::Mat &distortion() {return mDistortion;}
    const cv::Mat &extrinsic() {return mExtrinsic;}
    const CameraModel &model() {return mModel;}

protected:
    int mW, mH;
    int mScale = 1;
    cv::Mat mMapX, mMapY;
    bool mInitUndistortRectifyMap = false;
    double mFx, mFy, mCx, mCy;
    // 3*3
    cv::Mat mIntrinsic;
    // 1*4 or 1*5 or 1*8
    cv::Mat mDistortion;
    // 4*4
    cv::Mat mExtrinsic;
    // record camera model(pinhole fisheye etc.)
    CameraModel mModel;
};

} // namespace stereye
