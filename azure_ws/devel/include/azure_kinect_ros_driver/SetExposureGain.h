// Generated by gencpp from file azure_kinect_ros_driver/SetExposureGain.msg
// DO NOT EDIT!


#ifndef AZURE_KINECT_ROS_DRIVER_MESSAGE_SETEXPOSUREGAIN_H
#define AZURE_KINECT_ROS_DRIVER_MESSAGE_SETEXPOSUREGAIN_H

#include <ros/service_traits.h>


#include <azure_kinect_ros_driver/SetExposureGainRequest.h>
#include <azure_kinect_ros_driver/SetExposureGainResponse.h>


namespace azure_kinect_ros_driver
{

struct SetExposureGain
{

typedef SetExposureGainRequest Request;
typedef SetExposureGainResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct SetExposureGain
} // namespace azure_kinect_ros_driver


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::azure_kinect_ros_driver::SetExposureGain > {
  static const char* value()
  {
    return "118f5ae9e1aacf44af9d676470ddbbdf";
  }

  static const char* value(const ::azure_kinect_ros_driver::SetExposureGain&) { return value(); }
};

template<>
struct DataType< ::azure_kinect_ros_driver::SetExposureGain > {
  static const char* value()
  {
    return "azure_kinect_ros_driver/SetExposureGain";
  }

  static const char* value(const ::azure_kinect_ros_driver::SetExposureGain&) { return value(); }
};


// service_traits::MD5Sum< ::azure_kinect_ros_driver::SetExposureGainRequest> should match
// service_traits::MD5Sum< ::azure_kinect_ros_driver::SetExposureGain >
template<>
struct MD5Sum< ::azure_kinect_ros_driver::SetExposureGainRequest>
{
  static const char* value()
  {
    return MD5Sum< ::azure_kinect_ros_driver::SetExposureGain >::value();
  }
  static const char* value(const ::azure_kinect_ros_driver::SetExposureGainRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::azure_kinect_ros_driver::SetExposureGainRequest> should match
// service_traits::DataType< ::azure_kinect_ros_driver::SetExposureGain >
template<>
struct DataType< ::azure_kinect_ros_driver::SetExposureGainRequest>
{
  static const char* value()
  {
    return DataType< ::azure_kinect_ros_driver::SetExposureGain >::value();
  }
  static const char* value(const ::azure_kinect_ros_driver::SetExposureGainRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::azure_kinect_ros_driver::SetExposureGainResponse> should match
// service_traits::MD5Sum< ::azure_kinect_ros_driver::SetExposureGain >
template<>
struct MD5Sum< ::azure_kinect_ros_driver::SetExposureGainResponse>
{
  static const char* value()
  {
    return MD5Sum< ::azure_kinect_ros_driver::SetExposureGain >::value();
  }
  static const char* value(const ::azure_kinect_ros_driver::SetExposureGainResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::azure_kinect_ros_driver::SetExposureGainResponse> should match
// service_traits::DataType< ::azure_kinect_ros_driver::SetExposureGain >
template<>
struct DataType< ::azure_kinect_ros_driver::SetExposureGainResponse>
{
  static const char* value()
  {
    return DataType< ::azure_kinect_ros_driver::SetExposureGain >::value();
  }
  static const char* value(const ::azure_kinect_ros_driver::SetExposureGainResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // AZURE_KINECT_ROS_DRIVER_MESSAGE_SETEXPOSUREGAIN_H
