#include "Motor.h"
#include <termio.h>
#include <stdio.h> 
#include <atomic>
using namespace stereye;

std::atomic<int> lastKey;
std::shared_ptr<Motor> pMotor;
ros::Time lastStamp;

int scanKeyboard() {
    int in;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0,&stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0,&stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&new_settings);
    in = getchar();
    tcsetattr(0,TCSANOW,&stored_settings);
    return in;
}

void checkThread() {
    ros::Rate loop_rate(5);
    while (ros::ok()) {
        // didnot receive keyboard for a long time, stop robot
        if (ros::Time::now() > lastStamp + ros::Duration(0.25)) {
            pMotor->move(0, 0, 0);
            loop_rate.sleep();
            continue;
        }
        switch (lastKey) {
            // a
            case 97: {
                pMotor->move(0, 10, 0);
                break;
            }
            // d
            case 100: {
                pMotor->move(0, -10, 0);
                break;
            }
            // w
            case 119: {
                pMotor->move(10, 0, 0);
                break;
            }
            // s
            case 115: {
                pMotor->move(-10, 0, 0);
                break;
            }
        }
        loop_rate.sleep();
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "move_node");
    pMotor = std::make_shared<Motor>();
    pMotor->start();
    sleep(2);
    std::thread checker(&checkThread);
    lastStamp = ros::Time::now();

    while(ros::ok()) {
        lastKey = scanKeyboard();
        lastStamp = ros::Time::now();
        // printf(":%d",scanKeyboard());
    }

    pMotor->stop();
    if (checker.joinable()) checker.join();
    return 0;
}
