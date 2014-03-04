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

// using actionlib:
//#include <actionlib/client/simple_action_client.h>
//#include <TFG/LearnAction.h>

//typedef actionlib::SimpleActionClient <TFG::LearnAction> Client;

//int main (int argc, char ** argv)
//{
//    ros::init(argc, argv, "learn_client");
//    Client client ("learn", true); //true --> don't need ros::spin()
//    client.waitForServer();

//    TFG::LearnGoal goal;
//    //fill in goal here
//    goal.hand="I'm learning";

//    client.sendGoal(goal);
//    client.waitForResult(ros::Duration(5.0));
//    if (client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
//        printf("learn phase completed");

//    return 0;

//}
