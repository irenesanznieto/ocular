#include "EventHandlerNode.h"

EventHandlerNode::EventHandlerNode()
{
    event_pub=nh.advertise<TFG::EventHandler>("event", 1);
    skeleton_sub=nh.subscribe<pi_tracker::Skeleton>("skeleton", 1, &EventHandlerNode::event_cb, this);

}

void EventHandlerNode::event_cb(const pi_tracker::SkeletonConstPtr &msg)
{
    event_pub.publish(eventHandler.select_event_hand(*msg));
}

