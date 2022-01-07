#! /bin/bash

. $(dirname $0)/config.sh

cd $CART_DIR

echo "$SHELL"
source $ROS_ROOT
source devel/setup.bash

if [[ "$NEOTIC" = "ture" ]]; then
    source $CART_ROOT/devel_isolated/setup.bash
fi

if [[ "$CART_MODE" = "ONLINE" && "$CART_UI" = "ON" ]]; then
    echo "Running online mode with rviz"
    roslaunch mapping_robot online_ui.launch
fi

if [[ "$CART_MODE" = "OFFLINE" && "$CART_UI" = "ON" ]]; then
    echo "Running offline mode with rviz"
    roslaunch mapping_robot offline_ui.launch bag_filenames:=$BAG_FILE_DIR/$BAG_FILE_NAME
fi

if [[ "$CART_MODE" = "ONLINE" && "$CART_UI" = "OFF" ]]; then
    echo "Running online mode without rviz"
    roslaunch mapping_robot online_no_ui.launch
    wait
fi

if [[ "$CART_MODE" = "OFFLINE" && "$CART_UI" = "OFF" ]]; then
    echo "Running offline mode without rviz"
    roslaunch mapping_robot offline_no_ui.launch bag_filenames:=$BAG_FILE_DIR/$BAG_FILE_NAME
fi

 

# rosrun cartographer_ros cartographer_pbstream_to_ros_map -map_filestem=$MAP_DIR/$MAP_FILE_NAME -pbstream_filename=$BAG_FILE_DIR/$BAG_FILE_NAME.pbstream

roslaunch mapping_robot assets_writer.launch bag_filenames:=$BAG_FILE_DIR/$BAG_FILE_NAME pose_graph_filename:=$BAG_FILE_DIR/$BAG_FILE_NAME.pbstream
