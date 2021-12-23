#pragma once
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/LaserScan.h>
#include "Param.h"
#include "Motor.h"
#include "Utils.h"
#include <QObject>
#include <QDebug>
#include <QThread>
#include <QProcess>
#include <QDateTime>
#include <QFileDialog>
#include <QDir>
namespace stereye {

class Worker: public QObject {
    Q_OBJECT
public:
    explicit Worker(std::shared_ptr<Param> &param, QObject *parent = nullptr);
    ~Worker();

public slots:
	void startSensor();
    void stopSensor();
	void startRecord();
    void stopRecord();
    void parseData(QString path);

signals:
	void startSensorDone(void);
    void stopSensorDone(void);
	void startRecordDone(void);
	void stopRecordDone(void);
    void parseDataDone(void);


private:
    // enum STATE {
    //     NONE=0,
        
    // }
    void cameraCallback(const sensor_msgs::ImageConstPtr &);
    void lidarCallback(const sensor_msgs::LaserScan::ConstPtr &);

    std::shared_ptr<Param> mpParam;
    std::shared_ptr<Motor> mpMotor;
    ros::Subscriber mCameraSub;
    ros::Subscriber mLidarSub;
    std::atomic<bool> mAzureOk;
    std::atomic<bool> mLidarOk;

    QString mCurDateTime;
    QProcess* mpLidarProcess;
    QProcess* mpCameraProcess;
    QProcess* mpSlamProcess;
    QProcess* mpSlamHelperProcess;
    QProcess* mpRecorderProcess;
    QProcess* mpParserProcess;
    QProcess* mpCleaner;
};

} // namespace stereye