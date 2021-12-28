#!/bin/bash

. $(dirname $0)/config.sh

cd $LASER_DIR

source $ROS_ROOT
source devel/setup.bash
roslaunch pavo_ros pavo_scan.launch

