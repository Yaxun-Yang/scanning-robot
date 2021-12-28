#! /bin/bash

. $(dirname $0)/config.sh

source $ROS_ROOT



# start laser
cd $SCRIPTS_DIR

if [[ "$CART_MODE" = "ONLINE" ]]; then
echo "Running laser"
bash laser_run.sh
fi

# start cartographer

bash cartographer_run.sh

