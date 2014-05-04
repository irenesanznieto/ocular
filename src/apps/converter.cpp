#include <iostream>
#include <ros/ros.h>
#include "../libraries/nodes/ConverterNode.h"

int main (int argc,char* argv[])
{
    ros::init(argc, argv, "CONVERTER");
    ConverterNode converterNode;

    ros::spin();

    return 0;

}
