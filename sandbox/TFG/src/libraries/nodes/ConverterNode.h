#ifndef CONVERTER_NODE_H
#define CONVERTER_NODE_H

#include <ros/ros.h>
#include <pi_tracker/Skeleton.h>
#include <TFG/HandLoc.h>
//#include <std_msgs/String.h>

#include "../libraries/converter.h"

class ConverterNode
{
public:
    ConverterNode();

private:

    ros::NodeHandle nh;
    ros::Subscriber input_sub;
    ros::Publisher output_sub;

    Converter converterObject;

    void converter_cb(const pi_tracker::SkeletonConstPtr &);

};
#endif // CONVERTER_NODE_H
