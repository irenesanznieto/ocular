#ifndef CONVERTER_H
#define CONVERTER_H
#include <ros/ros.h>
#include <pi_tracker/Skeleton.h>
#include <TFG/HandLoc.h>
#include <std_msgs/String.h>

class Converter 
{
public:
    Converter();

private:

    ros::NodeHandle nh;
    ros::Subscriber input_sub;
    ros::Publisher output_sub;

    void input_callback(const pi_tracker::SkeletonConstPtr &);

};
#endif // CONVERTER_H
