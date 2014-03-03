#include <actionlib/server/simple_action_server.h>
#include <TFG/LearnAction.h>

typedef actionlib::SimpleActionServer <TFG::LearnAction> Server;

void execute (const TFG::LearnGoalConstPtr & goal, Server * as)
{
    //do all the learning of the new object etc.
    as->setSucceeded();
}

int main (int argc, char ** argv)
{
    ros::init(argc, argv, "learn_server");
    ros::NodeHandle n;
    Server server(n, "learn", boost::bind(&execute, _1, &server), false);
    server.start();
    ros::spin();
    return 0;

}
