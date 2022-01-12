#!/bin/bash

. $(dirname $0)/config.sh


source $ROS_ROOT
source $ROOT_DIR/devel/setup.bash

roslaunch nav configuration.launch
roslaunch nav move_base.launch

