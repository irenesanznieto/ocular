#include <TFG/EventHandler.h>
#include <ros/ros.h>
#include "../libraries/nodes/EventHandlerNode.h"

int main (int argc,char* argv[])
{
    ros::init(argc, argv, "EVENT_HANDLER");
    EventHandlerNode eventhandler;

    ros::spin();

    return 0;
}
