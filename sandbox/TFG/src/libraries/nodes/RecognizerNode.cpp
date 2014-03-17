#include "RecognizerNode.h"

RecognizerNode::RecognizerNode()
{
    descriptors2D_sub=nh.subscribe<TFG::HandImage>("descriptors2D", 1, &RecognizerNode::descriptors2D_cb, this);
    object_pub=nh.advertise<std_msgs::Int32>("object_id", 1);
    event_sub=nh.subscribe<TFG::EventHandler>("event", 1, &RecognizerNode::setEvent, this);

    recognize=true; //the default mode is recognizer
}


void RecognizerNode::descriptors2D_cb(const TFG::HandImageConstPtr & msg)
{
    if (recognize)      //If the mode is recognize
    {
        //    match & publish the resulting object ID
        object_pub.publish(matcher.match2D(msg));
    }
}

void RecognizerNode::setEvent(const TFG::EventHandlerConstPtr & msg)
{
    if (msg->event=="learn")
    {
        recognize=false;
    }
    else if (msg->event=="recognize")
    {
        recognize=true;
    }
}
