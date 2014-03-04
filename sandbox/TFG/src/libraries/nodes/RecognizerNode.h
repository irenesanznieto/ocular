#ifndef RECOGNIZERNODE_H
#define RECOGNIZERNODE_H

#include <ros/ros.h>
#include "../libraries/matcher.h"
#include <TFG/HandImage.h>
#include <std_msgs/Int32.h>

class RecognizerNode
{
public:
    RecognizerNode();
    ros::NodeHandle nh;
    ros::Publisher object_pub;
    ros::Subscriber descriptors2D_sub;

private:
    Matcher matcher;
    void descriptors2D_cb(const TFG::HandImageConstPtr & );

};

#endif // RECOGNIZERNODE_H
