#include "mainwindow.h"
#include "Param.h"
#include <ros/ros.h>
#include <QApplication>

void fillParam(ros::NodeHandle &nh, std::shared_ptr<stereye::Param> &param) {
    std::string calibrationPath;
    std::string lidarBash, lidarRemoteIp, lidarHostIp;
    std::string cameraBash, workerBash;
    std::string recorderPath, exportPath;

    nh.getParam("jpg_topic", param->mJpgTopic);
    nh.getParam("depth_topic", param->mDepthTopic);
    nh.getParam("lidar_topic", param->mLidarTopic);
    nh.getParam("calibration_path", calibrationPath);
    nh.getParam("lidar_bash", lidarBash);
    nh.getParam("lidar_remote_ip", lidarRemoteIp);
    nh.getParam("lidar_host_ip", lidarHostIp);
    nh.getParam("camera_bash", cameraBash);
    nh.getParam("worker_bash", workerBash);
    nh.getParam("recorder_path", recorderPath);
    nh.getParam("export_path", exportPath);

    param->mCalibrationPath = QString::fromStdString(calibrationPath);
    param->mLidarBash = QString::fromStdString(lidarBash);
    param->mLidarRemoteIp = QString::fromStdString(lidarRemoteIp);
    param->mLidarHostIp = QString::fromStdString(lidarHostIp);
    param->mCameraBash = QString::fromStdString(cameraBash);
    param->mWorkerBash = QString::fromStdString(workerBash);
    param->mRecorderPath = QString::fromStdString(recorderPath);
    param->mExportPath = QString::fromStdString(exportPath);
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "gui_node");
    ros::NodeHandle nh("~");

    auto param = std::make_shared<stereye::Param>();
    fillParam(nh, param);

    QApplication a(argc, argv);
    MainWindow w(param);
    w.show();
    a.exec();
    ros::shutdown();
    return 0;
}
