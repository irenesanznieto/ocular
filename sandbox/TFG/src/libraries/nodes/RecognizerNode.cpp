#include "RecognizerNode.h"

RecognizerNode::RecognizerNode()
{
    descriptors2D_sub=nh.subscribe<TFG::HandImage>("descriptors2D", 1, &RecognizerNode::descriptors2D_cb, this);
    object_pub=nh.advertise<std_msgs::Int32>("object_id", 1);

}


void RecognizerNode::descriptors2D_cb(const TFG::HandImageConstPtr & msg)
{
//    match & obtain results
    int object_id=matcher.match2D(msg);

//    publish object name
    object_pub.publish(object_id);

}
