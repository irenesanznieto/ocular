#include <iostream>
#include <ros/ros.h>
#include "../libraries/nodes/TrainerNode.h"


int main (int argc,char* argv[])
{
    ros::init(argc, argv, "LEARNER");
//    try
//    {
        TrainerNode trainer;
//    }
//    catch(std::length_error & e)
//    {
//        ROS_ERROR("exception catched");
//    }

    ros::spin();

    return 0;
}
