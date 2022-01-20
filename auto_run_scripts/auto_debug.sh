. $(dirname $0)/config.sh

source $ROS_ROOT

cd $ROOT_DIR

catkin_make --only-pkg-with-deps move

source $ROOT_DIR/devel/setup.bash

roslaunch move hw_control.launch

cd $SCRIPTS_DIR