#ifndef EVENTHANDLERNODE_H
#define EVENTHANDLERNODE_H
#include "../libraries/eventhandler.h"
#include <ros/ros.h>

class EventHandlerNode
{
public:
    EventHandlerNode();
    ros::NodeHandle nh;
    ros::Publisher event_pub;

//    subscribe to the skeleton message:
//    ros::Subscriber

private:
    EventHandler eventHandler;

};

#endif // EVENTHANDLERNODE_H
