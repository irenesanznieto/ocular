/* Auto-generated by genmsg_cpp for file /home/peko/tfg_git/sandbox/TFG/msg/HandLoc.msg */
#ifndef TFG_MESSAGE_HANDLOC_H
#define TFG_MESSAGE_HANDLOC_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Vector3.h"

namespace TFG
{
template <class ContainerAllocator>
struct HandLoc_ {
  typedef HandLoc_<ContainerAllocator> Type;

  HandLoc_()
  : header()
  , user_id(0)
  , name()
  , position()
  {
  }

  HandLoc_(const ContainerAllocator& _alloc)
  : header(_alloc)
  , user_id(0)
  , name(_alloc)
  , position(_alloc)
  {
  }

  typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
   ::std_msgs::Header_<ContainerAllocator>  header;

  typedef int32_t _user_id_type;
  int32_t user_id;

  typedef std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other >  _name_type;
  std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other >  name;

  typedef std::vector< ::geometry_msgs::Vector3_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::geometry_msgs::Vector3_<ContainerAllocator> >::other >  _position_type;
  std::vector< ::geometry_msgs::Vector3_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::geometry_msgs::Vector3_<ContainerAllocator> >::other >  position;


  typedef boost::shared_ptr< ::TFG::HandLoc_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::TFG::HandLoc_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct HandLoc
typedef  ::TFG::HandLoc_<std::allocator<void> > HandLoc;

typedef boost::shared_ptr< ::TFG::HandLoc> HandLocPtr;
typedef boost::shared_ptr< ::TFG::HandLoc const> HandLocConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::TFG::HandLoc_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::TFG::HandLoc_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace TFG

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::TFG::HandLoc_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::TFG::HandLoc_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::TFG::HandLoc_<ContainerAllocator> > {
  static const char* value() 
  {
    return "cfd3d4cfc901078d15846fcfd4a5dcb9";
  }

  static const char* value(const  ::TFG::HandLoc_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xcfd3d4cfc901078dULL;
  static const uint64_t static_value2 = 0x15846fcfd4a5dcb9ULL;
};

template<class ContainerAllocator>
struct DataType< ::TFG::HandLoc_<ContainerAllocator> > {
  static const char* value() 
  {
    return "TFG/HandLoc";
  }

  static const char* value(const  ::TFG::HandLoc_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::TFG::HandLoc_<ContainerAllocator> > {
  static const char* value() 
  {
    return "Header header\n\
int32 user_id\n\
string[] name\n\
geometry_msgs/Vector3[] position\n\
\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Vector3\n\
# This represents a vector in free space. \n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
";
  }

  static const char* value(const  ::TFG::HandLoc_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct HasHeader< ::TFG::HandLoc_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct HasHeader< const ::TFG::HandLoc_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::TFG::HandLoc_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.header);
    stream.next(m.user_id);
    stream.next(m.name);
    stream.next(m.position);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct HandLoc_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::TFG::HandLoc_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::TFG::HandLoc_<ContainerAllocator> & v) 
  {
    s << indent << "header: ";
s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "user_id: ";
    Printer<int32_t>::stream(s, indent + "  ", v.user_id);
    s << indent << "name[]" << std::endl;
    for (size_t i = 0; i < v.name.size(); ++i)
    {
      s << indent << "  name[" << i << "]: ";
      Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.name[i]);
    }
    s << indent << "position[]" << std::endl;
    for (size_t i = 0; i < v.position.size(); ++i)
    {
      s << indent << "  position[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::geometry_msgs::Vector3_<ContainerAllocator> >::stream(s, indent + "    ", v.position[i]);
    }
  }
};


} // namespace message_operations
} // namespace ros

#endif // TFG_MESSAGE_HANDLOC_H
