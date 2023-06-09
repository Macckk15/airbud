// Generated by gencpp from file drone_controller/SetRefPose.msg
// DO NOT EDIT!


#ifndef DRONE_CONTROLLER_MESSAGE_SETREFPOSE_H
#define DRONE_CONTROLLER_MESSAGE_SETREFPOSE_H

#include <ros/service_traits.h>


#include <drone_controller/SetRefPoseRequest.h>
#include <drone_controller/SetRefPoseResponse.h>


namespace drone_controller
{

struct SetRefPose
{

typedef SetRefPoseRequest Request;
typedef SetRefPoseResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct SetRefPose
} // namespace drone_controller


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::drone_controller::SetRefPose > {
  static const char* value()
  {
    return "a121ec35e34f22c1f30911ae51c46c9f";
  }

  static const char* value(const ::drone_controller::SetRefPose&) { return value(); }
};

template<>
struct DataType< ::drone_controller::SetRefPose > {
  static const char* value()
  {
    return "drone_controller/SetRefPose";
  }

  static const char* value(const ::drone_controller::SetRefPose&) { return value(); }
};


// service_traits::MD5Sum< ::drone_controller::SetRefPoseRequest> should match
// service_traits::MD5Sum< ::drone_controller::SetRefPose >
template<>
struct MD5Sum< ::drone_controller::SetRefPoseRequest>
{
  static const char* value()
  {
    return MD5Sum< ::drone_controller::SetRefPose >::value();
  }
  static const char* value(const ::drone_controller::SetRefPoseRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::drone_controller::SetRefPoseRequest> should match
// service_traits::DataType< ::drone_controller::SetRefPose >
template<>
struct DataType< ::drone_controller::SetRefPoseRequest>
{
  static const char* value()
  {
    return DataType< ::drone_controller::SetRefPose >::value();
  }
  static const char* value(const ::drone_controller::SetRefPoseRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::drone_controller::SetRefPoseResponse> should match
// service_traits::MD5Sum< ::drone_controller::SetRefPose >
template<>
struct MD5Sum< ::drone_controller::SetRefPoseResponse>
{
  static const char* value()
  {
    return MD5Sum< ::drone_controller::SetRefPose >::value();
  }
  static const char* value(const ::drone_controller::SetRefPoseResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::drone_controller::SetRefPoseResponse> should match
// service_traits::DataType< ::drone_controller::SetRefPose >
template<>
struct DataType< ::drone_controller::SetRefPoseResponse>
{
  static const char* value()
  {
    return DataType< ::drone_controller::SetRefPose >::value();
  }
  static const char* value(const ::drone_controller::SetRefPoseResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // DRONE_CONTROLLER_MESSAGE_SETREFPOSE_H
