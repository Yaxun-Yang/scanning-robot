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

bool Motor::move(float velocity, float rotate, float head) {
    // todo: remove those limits
    if (velocity > 20) velocity = 20;
    if (velocity < -20) velocity = -20;
    if (rotate > 20) rotate = 20;
    if (rotate < -20) rotate = -20;

    uint8_t *v = (uint8_t *)&velocity;
    uint8_t *r = (uint8_t *)&rotate;
    uint8_t *h = (uint8_t *)&head;
    std::vector<uint8_t> buffer{0x55, 0xaa, 0x0e, 0x03, v[0], v[1], v[2], v[3], r[0], r[1], r[2], r[3], h[0], h[1], h[2], h[3]};
    
    uint8_t crc;
    for (unsigned int i = 2; i < buffer.size(); ++i) {
        crc += buffer[i];
    }
    crc = (0xff)&(~crc);
    buffer.push_back(crc);

    std::cout << "Motor::move called! data:";
    for (unsigned int i = 0; i < buffer.size(); ++i) {
        std::cout << std::hex << int(buffer[i]) << "-";
    }
    std::cout << std::endl;
    std::lock_guard<std::mutex> lock(mIOLock);
    mpSerial->write(buffer.data(), buffer.size());
}

bool Motor::autoBalance(bool on) {
    std::vector<uint8_t> buffer;
    if (on) buffer = {0x55, 0xaa, 0x03, 0x04, 0x01, 0xf7};
    else buffer = {0x55, 0xaa, 0x03, 0x04, 0x00, 0xf8};
    
    std::lock_guard<std::mutex> lock(mIOLock);
    mpSerial->write(buffer.data(), buffer.size());
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
