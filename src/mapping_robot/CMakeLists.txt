cmake_minimum_required(VERSION 3.5)
project(mapping_robot)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14  -O3")

add_definitions(-DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
option(STEREYE_PC "PC mode" ON)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "amd64.*|x86_64.*|AMD64.*")
else()
    # system platform not match pc, set to OFF
    set(STEREYE_PC OFF)
endif()

set(cartographer_DIR /opt/ros/melodic/share/cartographer)
find_package(catkin REQUIRED COMPONENTS
    cv_bridge
    roscpp
    sensor_msgs
    std_srvs
    rosbag
    message_filters
    tf
    eigen_conversions
    rviz
    serial
    cartographer
    cartographer_ros
    cartographer_ros_msgs
)

if (STEREYE_PC)
    add_subdirectory(third/nvdecoder/JPEGDecoder)
endif()

catkin_package(
)

# find_package(PCL REQUIRED COMPONENTS io filters common)
find_package(OpenCV 3.2 REQUIRED core highgui imgproc imgcodecs calib3d)
find_package(Eigen3 REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    # this includes ui_xxxx.h
    ${CMAKE_CURRENT_BINARY_DIR}
    third/nvdecoder/JPEGDecoder
    /usr/include/lua5.2
)

QT5_WRAP_CPP(moc_srcs include/mainwindow.h include/Worker.h)
QT5_WRAP_UI(moc_uis src/mainwindow.ui)

add_library(${PROJECT_NAME}
    src/BagRecorder.cpp
    src/Camera.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${OpenCV_LIBS}
)

add_executable(recorder_node
    src/recorder_node.cpp
)

target_link_libraries(
    recorder_node
    ${PROJECT_NAME}
)

add_executable(gui_node
    src/gui_node.cpp
    src/mainwindow.cpp
    src/Worker.cpp
    src/Motor.cpp
    ${moc_srcs}
    ${moc_uis}
)

target_link_libraries(
    gui_node
    ${PROJECT_NAME}
)

QT5_USE_MODULES(gui_node Widgets Core Gui)

if (STEREYE_PC)
    add_executable(parser_node
        src/BagParser.cpp
        src/parser_node.cpp
    )
    target_link_libraries(
        parser_node
        ${PROJECT_NAME}
        decoder_lib
    )

    add_executable(pbstream_node
        src/pbstream_node.cpp
    )

    target_link_libraries(
        pbstream_node
        ${PROJECT_NAME}
        cartographer
    )
endif()
