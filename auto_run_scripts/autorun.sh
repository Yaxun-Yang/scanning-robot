#! /bin/bash

. $(dirname $0)/config.sh

source $ROS_ROOT

source $ROOT_DIR/devel/setup.bash

# start laser
cd $SCRIPTS_DIR

if [[ "$CART_MODE" = "ONLINE" ]]; then
echo "Running laser"
bash laser_run.sh&
fi
sleep 5
echo "Running cartographer"
# start cartographer
bash cartographer_run.sh
echo "Running navigation"
#start navigation
#bash nav_run.sh&

