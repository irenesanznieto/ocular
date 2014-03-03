#include <TFG/EventHandler.h>
#include <ros/ros.h>
#include "../libraries/nodes/EventHandlerNode.h"

int main (int argc,char* argv[])
{
    ros::init(argc, argv, "CONVERTER");
    EventHandler eventhandler;

    ros::spin();

    return 0;
}
