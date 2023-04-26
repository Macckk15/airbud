// Generated by gencpp from file tello_driver/MoveDownResponse.msg
// DO NOT EDIT!


#ifndef TELLO_DRIVER_MESSAGE_MOVEDOWNRESPONSE_H
#define TELLO_DRIVER_MESSAGE_MOVEDOWNRESPONSE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace tello_driver
{
template <class ContainerAllocator>
struct MoveDownResponse_
{
  typedef MoveDownResponse_<ContainerAllocator> Type;

  MoveDownResponse_()
    : command_status(false)  {
    }
  MoveDownResponse_(const ContainerAllocator& _alloc)
    : command_status(false)  {
  (void)_alloc;
    }



   typedef uint8_t _command_status_type;
  _command_status_type command_status;





  typedef boost::shared_ptr< ::tello_driver::MoveDownResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::tello_driver::MoveDownResponse_<ContainerAllocator> const> ConstPtr;

}; // struct MoveDownResponse_

typedef ::tello_driver::MoveDownResponse_<std::allocator<void> > MoveDownResponse;

typedef boost::shared_ptr< ::tello_driver::MoveDownResponse > MoveDownResponsePtr;
typedef boost::shared_ptr< ::tello_driver::MoveDownResponse const> MoveDownResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::tello_driver::MoveDownResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::tello_driver::MoveDownResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::tello_driver::MoveDownResponse_<ContainerAllocator1> & lhs, const ::tello_driver::MoveDownResponse_<ContainerAllocator2> & rhs)
{
  return lhs.command_status == rhs.command_status;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::tello_driver::MoveDownResponse_<ContainerAllocator1> & lhs, const ::tello_driver::MoveDownResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace tello_driver

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::tello_driver::MoveDownResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::tello_driver::MoveDownResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::tello_driver::MoveDownResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::tello_driver::MoveDownResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::tello_driver::MoveDownResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::tello_driver::MoveDownResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::tello_driver::MoveDownResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "943f51d9faa4a44a232934ed3bd1b114";
  }

  static const char* value(const ::tello_driver::MoveDownResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x943f51d9faa4a44aULL;
  static const uint64_t static_value2 = 0x232934ed3bd1b114ULL;
};

template<class ContainerAllocator>
struct DataType< ::tello_driver::MoveDownResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "tello_driver/MoveDownResponse";
  }

  static const char* value(const ::tello_driver::MoveDownResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::tello_driver::MoveDownResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool    command_status\n"
;
  }

  static const char* value(const ::tello_driver::MoveDownResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::tello_driver::MoveDownResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.command_status);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct MoveDownResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::tello_driver::MoveDownResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::tello_driver::MoveDownResponse_<ContainerAllocator>& v)
  {
    s << indent << "command_status: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.command_status);
  }
};

} // namespace message_operations
} // namespace ros

#endif // TELLO_DRIVER_MESSAGE_MOVEDOWNRESPONSE_H