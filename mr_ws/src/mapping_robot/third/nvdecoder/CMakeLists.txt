cmake_minimum_required(VERSION 3.0)
project(jpegdecoder)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O3 -fPIC")

# fix libnvjpeg stuff missing
link_directories(
  /usr/lib/aarch64-linux-gnu/tegra
)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS 
             cv_bridge roscpp rospy sensor_msgs std_msgs
)


## System dependencies are found with CMake's conventions
find_package(OpenCV 3.4 REQUIRED)

catkin_package(
  LIBRARIES nvdecoder
  CATKIN_DEPENDS cv_bridge roscpp rospy sensor_msgs std_msgs
  DEPENDS OpenCV
)

###########
## Build ##
###########
add_subdirectory(JPEGDecoder)
include_directories(
  JPEGDecoder
  /usr/src/jetson_multimedia_api/include/libjpeg-8b
)

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${OpenCV_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

# libraries
set(Libraries
   ${OpenCV_LIBRARIES}
   ${catkin_LIBRARIES}
   ${cv_bridge_LIBRARIES}
   decoder_lib
)

add_executable(
    jpegdecoder
    decoderROSWrapper.cpp
)

target_link_libraries(
    jpegdecoder
    ${Libraries}
)
