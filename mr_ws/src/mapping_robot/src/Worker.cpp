#include "Worker.h"

namespace stereye {
Worker::Worker(std::shared_ptr<Param> &param, QObject *parent): mpParam(param) {
    mpLidarProcess = new QProcess(this);
    mpCameraProcess = new QProcess(this);
    mpSlamProcess = new QProcess(this);
    mpSlamHelperProcess = new QProcess(this);
    mpRecorderProcess = new QProcess(this);
    mpParserProcess = new QProcess(this);
    mpCleaner = new QProcess(this);
    mpMotor = std::make_shared<Motor>(115200, "/dev/ttyTHS2");
}

Worker::~Worker() {
    mpCleaner->execute(QString("kill -SIGINT %1").arg(mpLidarProcess->processId()));
    mpCleaner->execute(QString("kill -SIGINT %1").arg(mpCameraProcess->processId()));
    mpCleaner->execute(QString("kill -SIGINT %1").arg(mpSlamProcess->processId()));
    mpCleaner->execute(QString("kill -SIGINT %1").arg(mpRecorderProcess->processId()));
    mpCleaner->execute(QString("kill -SIGINT %1").arg(mpParserProcess->processId()));
}

void Worker::cameraCallback(const sensor_msgs::ImageConstPtr &){
    qDebug() << "cameraCallback";
    mCameraSub.shutdown();
    mAzureOk = true;
}

void Worker::lidarCallback(const sensor_msgs::LaserScan::ConstPtr &) {
    qDebug() << "lidarCallback";
    mLidarSub.shutdown();
    mLidarOk = true;
}

void Worker::startSensor() {
    mpMotor->start();
    qDebug() << "Worker::startSensor";
    mpCleaner->execute("bash -c \"killall azure_kinect_ros_driver\"");
    QString lidarCmd = QString("bash -c \"source %1 && roslaunch pavo_ros pavo_scan.launch lidar_ip:=%2 host_ip:=%3\"")
                                                                .arg(mpParam->mLidarBash).arg(mpParam->mLidarRemoteIp).arg(mpParam->mLidarHostIp);
    mpLidarProcess->start(lidarCmd);
    QString cameraCmd = QString("bash -c \"source %1 && roslaunch azure_kinect_ros_driver driver.launch\"").arg(mpParam->mCameraBash);
    mpCameraProcess->start(cameraCmd);
    mAzureOk = false;
    mLidarOk = false;
    // QThread::sleep(5);
    ros::NodeHandle nh;
    mCameraSub = nh.subscribe(mpParam->mDepthTopic, 1, &Worker::cameraCallback, this);
    mLidarSub = nh.subscribe(mpParam->mLidarTopic, 1, &Worker::lidarCallback, this);
    while (!mAzureOk || !mLidarOk) {
        QThread::msleep(100);
        ros::spinOnce();
    }
    QString slamCmd = QString("bash -c \"source %1 && cd %2 && roslaunch cartographer/demo_no_ui.launch\"")
                                                              .arg(mpParam->mWorkerBash).arg(PROJECT_SOURCE_DIR);
    mpSlamProcess->start(slamCmd);
    QThread::sleep(2);
    emit startSensorDone();
}

void Worker::stopSensor() {
    qDebug() << "Worker::stopSensor";
    mpMotor->stop();
    mpCleaner->execute(QString("kill -SIGINT %1").arg(mpLidarProcess->processId()));
    mpCleaner->execute(QString("kill -SIGINT %1").arg(mpCameraProcess->processId()));
    mpCleaner->execute(QString("kill -SIGINT %1").arg(mpSlamProcess->processId()));
    emit stopSensorDone();
}

void Worker::startRecord() {
    qDebug() << "Worker::startRecord";
    mCurDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
    QString recorderCmd = QString("bash -c \"source %1 && roslaunch mapping_robot record.launch bag_path:=%2/%3.bag\"")
                                                                        .arg(mpParam->mWorkerBash).arg(mpParam->mRecorderPath).arg(mCurDateTime);
    mpRecorderProcess->start(recorderCmd);
    emit startRecordDone();
}

void Worker::stopRecord() {
    qDebug() << "Worker::stopRecord";
    mpCleaner->execute(QString("kill -SIGINT %1").arg(mpRecorderProcess->processId()));
    QString pbstreamCmd = QString("bash -c \"rosservice call /finish_trajectory  0 && rosservice call /write_state '{filename: \"%1/data.pbstream\"}'\"")
                                                                        .arg(mpParam->mRecorderPath);
    mpSlamHelperProcess->execute(pbstreamCmd);
    utils::mkdirs((mpParam->mExportPath+"/"+mCurDateTime).toStdString());
    mpSlamHelperProcess->execute(QString("bash -c \"mv %1/*.bag %2/%3/\"").arg(mpParam->mRecorderPath).arg(mpParam->mExportPath).arg(mCurDateTime));
    mpSlamHelperProcess->execute(QString("bash -c \"mv %1/*.pbstream %2/%3/\"").arg(mpParam->mRecorderPath).arg(mpParam->mExportPath).arg(mCurDateTime));
    emit stopRecordDone();
}

void Worker::parseData(QString path) {
    qDebug() << "Worker::parseData";
    qDebug() << path;
    QDir dir = QDir(path);
    // if(!dir->exists())
    //     return false;
    QStringList filter;
    QString bagpath;
    QString pbpath;
    filter << "*.pbstream";
    filter = dir.entryList(filter, QDir::Files | QDir::Readable, QDir::Name);
    if (filter.size() == 1) {
        pbpath = path+"/"+filter.at(0);
        qDebug() << "pbpath:" << pbpath;
    }
    filter.clear();
    filter << "*.bag";
    filter = dir.entryList(filter, QDir::Files | QDir::Readable, QDir::Name);
    if (filter.size() == 1) {
        bagpath = path+"/"+filter.at(0);
        qDebug() << "bagpath:" << bagpath;
    }
    if (!bagpath.isEmpty() && !pbpath.isEmpty()) {
        mpSlamHelperProcess->execute(QString("bash -c \"source %1 && rosrun mapping_robot pbstream_node %2 %3\"")
                                                                        .arg(mpParam->mWorkerBash).arg(pbpath).arg(path+"/poses.txt"));
        mpSlamHelperProcess->execute(QString("bash -c \"source %1 && roslaunch mapping_robot parse.launch bag_path:=%2 pose_path:=%3 export_path:=%4 calibration_path:=%5\"")
                                                                        .arg(mpParam->mWorkerBash).arg(bagpath).arg(path+"/poses.txt").arg(mpParam->mExportPath+"/"+filter.at(0).split(".").at(0)).arg(mpParam->mCalibrationPath));
    }
    emit parseDataDone();
}

} // namespace stereye
