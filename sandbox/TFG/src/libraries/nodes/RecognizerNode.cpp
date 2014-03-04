#include "RecognizerNode.h"

RecognizerNode::RecognizerNode()
{
    descriptors2D_sub=nh.subscribe<TFG::HandImage>("descriptors2D", 1, &RecognizerNode::descriptors2D_cb, this);
    object_pub=nh.advertise<std_msgs::Int32>("object_id", 1);

}


void RecognizerNode::descriptors2D_cb(const TFG::HandImageConstPtr & msg)
{
//    matcher.match2D(msg);

//    match & obtain results

//    publish object name
}
