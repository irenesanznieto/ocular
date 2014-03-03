
int main ()
{

}

// using actionlib
//#include <actionlib/client/simple_action_client.h>
//#include <TFG/LearnAction.h>

//typedef actionlib::SimpleActionClient <TFG::LearnAction> Client;

//int main (int argc, char ** argv)
//{
//    ros::init(argc, argv, "recognizer_client");
//    Client client ("recognize", false);      //true --> don't need ros::spin()
//    client.waitForServer();

//    TFG::LearnGoal goal;
//    //fill in goal here
//    goal.hand="I'm recognizing";

//    client.sendGoal(goal);
//    client.waitForResult(ros::Duration(5.0));
//    if (client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
//        printf("recognize phase completed");

//    ros::spin();

//    return 0;
//}
