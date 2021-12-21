#pragma once

#include <memory>
#include <iostream>
#include <unistd.h>
#include <mutex>
#include <thread>
#include <atomic>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

namespace serial {
    class Serial;
}

namespace stereye {

class Motor {
public:
    Motor(int baudrate=115200, const std::string &port="/dev/ttyTHS2");
    ~Motor();

    bool isWorking();
    void start();
    void stop();
    // control robot movement
    bool move(float velocity, float rotate, float head);
    // control robot auto balance
    bool autoBalance(bool on);

private:
    bool openSerial();
    bool readFromSerial();
    void statusCheckThread();

    int mBaudrate;
    std::string mPort;

    std::mutex mIOLock;  // inner lock
    bool mOk = false;     // current status
    std::atomic<bool> mRun;

    std::thread mStatusChecker;
    ros::Publisher mStatePub;

    std::shared_ptr<serial::Serial> mpSerial;    // serial port
};

} // namespace stereye
