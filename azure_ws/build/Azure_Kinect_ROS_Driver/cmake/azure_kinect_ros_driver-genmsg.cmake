# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "azure_kinect_ros_driver: 0 messages, 1 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/melodic/share/sensor_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/melodic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(azure_kinect_ros_driver_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/stereye/azure_ws/src/Azure_Kinect_ROS_Driver/srv/SetExposureGain.srv" NAME_WE)
add_custom_target(_azure_kinect_ros_driver_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "azure_kinect_ros_driver" "/home/stereye/azure_ws/src/Azure_Kinect_ROS_Driver/srv/SetExposureGain.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(azure_kinect_ros_driver
  "/home/stereye/azure_ws/src/Azure_Kinect_ROS_Driver/srv/SetExposureGain.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/azure_kinect_ros_driver
)

### Generating Module File
_generate_module_cpp(azure_kinect_ros_driver
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/azure_kinect_ros_driver
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(azure_kinect_ros_driver_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(azure_kinect_ros_driver_generate_messages azure_kinect_ros_driver_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/stereye/azure_ws/src/Azure_Kinect_ROS_Driver/srv/SetExposureGain.srv" NAME_WE)
add_dependencies(azure_kinect_ros_driver_generate_messages_cpp _azure_kinect_ros_driver_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(azure_kinect_ros_driver_gencpp)
add_dependencies(azure_kinect_ros_driver_gencpp azure_kinect_ros_driver_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS azure_kinect_ros_driver_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services
_generate_srv_eus(azure_kinect_ros_driver
  "/home/stereye/azure_ws/src/Azure_Kinect_ROS_Driver/srv/SetExposureGain.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/azure_kinect_ros_driver
)

### Generating Module File
_generate_module_eus(azure_kinect_ros_driver
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/azure_kinect_ros_driver
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(azure_kinect_ros_driver_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(azure_kinect_ros_driver_generate_messages azure_kinect_ros_driver_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/stereye/azure_ws/src/Azure_Kinect_ROS_Driver/srv/SetExposureGain.srv" NAME_WE)
add_dependencies(azure_kinect_ros_driver_generate_messages_eus _azure_kinect_ros_driver_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(azure_kinect_ros_driver_geneus)
add_dependencies(azure_kinect_ros_driver_geneus azure_kinect_ros_driver_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS azure_kinect_ros_driver_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(azure_kinect_ros_driver
  "/home/stereye/azure_ws/src/Azure_Kinect_ROS_Driver/srv/SetExposureGain.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/azure_kinect_ros_driver
)

### Generating Module File
_generate_module_lisp(azure_kinect_ros_driver
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/azure_kinect_ros_driver
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(azure_kinect_ros_driver_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(azure_kinect_ros_driver_generate_messages azure_kinect_ros_driver_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/stereye/azure_ws/src/Azure_Kinect_ROS_Driver/srv/SetExposureGain.srv" NAME_WE)
add_dependencies(azure_kinect_ros_driver_generate_messages_lisp _azure_kinect_ros_driver_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(azure_kinect_ros_driver_genlisp)
add_dependencies(azure_kinect_ros_driver_genlisp azure_kinect_ros_driver_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS azure_kinect_ros_driver_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services
_generate_srv_nodejs(azure_kinect_ros_driver
  "/home/stereye/azure_ws/src/Azure_Kinect_ROS_Driver/srv/SetExposureGain.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/azure_kinect_ros_driver
)

### Generating Module File
_generate_module_nodejs(azure_kinect_ros_driver
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/azure_kinect_ros_driver
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(azure_kinect_ros_driver_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(azure_kinect_ros_driver_generate_messages azure_kinect_ros_driver_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/stereye/azure_ws/src/Azure_Kinect_ROS_Driver/srv/SetExposureGain.srv" NAME_WE)
add_dependencies(azure_kinect_ros_driver_generate_messages_nodejs _azure_kinect_ros_driver_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(azure_kinect_ros_driver_gennodejs)
add_dependencies(azure_kinect_ros_driver_gennodejs azure_kinect_ros_driver_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS azure_kinect_ros_driver_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(azure_kinect_ros_driver
  "/home/stereye/azure_ws/src/Azure_Kinect_ROS_Driver/srv/SetExposureGain.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/azure_kinect_ros_driver
)

### Generating Module File
_generate_module_py(azure_kinect_ros_driver
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/azure_kinect_ros_driver
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(azure_kinect_ros_driver_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(azure_kinect_ros_driver_generate_messages azure_kinect_ros_driver_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/stereye/azure_ws/src/Azure_Kinect_ROS_Driver/srv/SetExposureGain.srv" NAME_WE)
add_dependencies(azure_kinect_ros_driver_generate_messages_py _azure_kinect_ros_driver_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(azure_kinect_ros_driver_genpy)
add_dependencies(azure_kinect_ros_driver_genpy azure_kinect_ros_driver_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS azure_kinect_ros_driver_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/azure_kinect_ros_driver)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/azure_kinect_ros_driver
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(azure_kinect_ros_driver_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(azure_kinect_ros_driver_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/azure_kinect_ros_driver)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/azure_kinect_ros_driver
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(azure_kinect_ros_driver_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(azure_kinect_ros_driver_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/azure_kinect_ros_driver)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/azure_kinect_ros_driver
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(azure_kinect_ros_driver_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(azure_kinect_ros_driver_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/azure_kinect_ros_driver)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/azure_kinect_ros_driver
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(azure_kinect_ros_driver_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(azure_kinect_ros_driver_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/azure_kinect_ros_driver)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/azure_kinect_ros_driver\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/azure_kinect_ros_driver
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(azure_kinect_ros_driver_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(azure_kinect_ros_driver_generate_messages_py sensor_msgs_generate_messages_py)
endif()
