#include <iostream>
#include <ros/ros.h>
#include "../libraries/nodes/TrainerNode.h"


int main (int argc,char* argv[])
{
    ros::init(argc, argv, "LEARNER");

    TrainerNode trainer;

    ros::spin();

    return 0;
}
