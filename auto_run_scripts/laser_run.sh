#!/bin/bash

. $(dirname $0)/config.sh


source $ROS_ROOT
source $ROOT_DIR/devel/setup.bash
roslaunch pavo_ros pavo_scan.launch

