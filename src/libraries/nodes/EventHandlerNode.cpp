#include "EventHandlerNode.h"

EventHandlerNode::EventHandlerNode()
{
    event_pub=nh.advertise<ocular::EventHandler>("event", 1);
    skeleton_sub=nh.subscribe<skeleton_markers::Skeleton>("skeleton", 1, &EventHandlerNode::event_cb, this);

}

void EventHandlerNode::event_cb(const skeleton_markers::SkeletonConstPtr &msg)
{
    event_pub.publish(eventHandler.select_event_hand(*msg));
}

