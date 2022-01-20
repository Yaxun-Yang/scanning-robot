#! /bin/bash
#ROS_ROOT=/opt/ros/noetic/setup.bash
ROS_ROOT=/opt/ros/melodic/setup.bash

ROOT_DIR=/home/stereye/scanning-robot

#ROOT_DIR=/home/yyxunn/scanning-robot

BAG_FILE_DIR=$ROOT_DIR/input
BAG_FILE_NAME=test.bag

MAP_DIR=$ROOT_DIR/output
MAP_FILE_NAME=test_map

SCRIPTS_DIR=$ROOT_DIR/auto_run_scripts


# how do you want to run cartographer?

#CART_MODE=ONLINE
CART_MODE=OFFLINE

# do you want to run rviz?
CART_UI=ON
#CART_UI=OFF

# whether run in neotic?
#NEOTIC=true
CART_ROOT=/home/yyxunn/cartographer_ws
NEOTIC=false