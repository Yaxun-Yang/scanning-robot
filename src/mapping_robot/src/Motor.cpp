#include "Motor.h"
#include <serial/serial.h>

namespace stereye {

Motor::Motor(int baudrate, const std::string &port): mBaudrate(baudrate), mPort(port) {
    mRun = false;
    // initialize serial
    mpSerial = std::make_shared<serial::Serial>();
    serial::Timeout timeout = serial::Timeout::simpleTimeout(200);
    mpSerial->setPort(mPort);
    mpSerial->setBaudrate(mBaudrate);
    mpSerial->setTimeout(timeout);
    ros::NodeHandle n;
    mStatePub = n.advertise<sensor_msgs::JointState>("/mapping_robot/state", 10);
}

Motor::~Motor() {
    stop();
    if (mpSerial) mpSerial->close();
    mpSerial = nullptr;
}

bool Motor::openSerial() {
    try {
        if (!mpSerial->isOpen()) mpSerial->open();
        mpSerial->available();
        mOk = true;
    } catch (...) {
        mpSerial->close();
        mOk = false;
        std::cout << "Serial port not available!" << std::endl;
    }
    return mOk;
}

bool Motor::readFromSerial() {
    std::lock_guard<std::mutex> lock(mIOLock);
    if (mOk) {
        try {
            if (mpSerial->available()) {
                // clean cache
                // mpSerial->flushInput();
                std::string data;
                size_t res = mpSerial->readline(data, 100);
                // std::cout << "Read from serial. data: " << data;
                // check data
                if (data.size()>20) {
                    char notUsed[100];
                    int hours, minutes;
                    float seconds, robot, head, vLeft, vRight;
                    int n = sscanf(data.c_str(), "%[^S]S:%d:%d:%f:Robot%f,Head%f,Left%f,Right%f\r",
                                                notUsed, &hours, &minutes, &seconds, &robot, &head, &vLeft, &vRight);
                    if (n == 8) {
                        //printf("--TS:%d:%d:%f:Robot%f,Head%f,Left%f,Right%f\n", hours, minutes, seconds, robot, head, vLeft, vRight);
                        sensor_msgs::JointState state;
                        state.header.stamp = ros::Time::now();
                        state.effort = {hours*60*60+minutes*60+seconds, robot, head};
                        state.velocity = {vLeft, vRight};
                        mStatePub.publish(state);
                        //ros::spinOnce();
                    }
                }
            }
        } catch (...) {
        } 
    }
    // if serial port error, return -1
    return mOk;
}


bool Motor::isWorking() {
    return mOk;
}

void Motor::statusCheckThread() {
    std::cout << "statusCheckThread started!" << std::endl;
    while (mRun) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));    // 100hz
        openSerial();
        readFromSerial();
    }
}

void Motor::start() {
    mRun = true;
    mStatusChecker = std::thread(&Motor::statusCheckThread, this);
}

void Motor::stop() {
    mRun = false;
    if (mStatusChecker.joinable()) mStatusChecker.join();
}

} // namespace stereye
