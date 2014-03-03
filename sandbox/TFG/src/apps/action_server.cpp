
int main ()
{

}


// using actionlib
//#include <actionlib/server/simple_action_server.h>
//#include <TFG/LearnAction.h>

//typedef actionlib::SimpleActionServer <TFG::LearnAction> Server;

//void execute (const TFG::LearnGoalConstPtr & goal, Server * as)
//{
//    //do all the learning of the new object etc.
//    as->setSucceeded();
////    as->shutdown();
//}

//int main (int argc, char ** argv)
//{
//    ros::init(argc, argv, "server");
//    ros::NodeHandle n;
////    int i=0;
////    std::cout <<i<<std::endl;
////    if (i>10)
////    {
////        Server server(n, "learn", boost::bind(&execute, _1, &server), false);
////        i++;
////        server.start();
////    }

////    else
////    {
////        i++;
//        Server server(n, "recognize", boost::bind(&execute, _1, &server), false);
//        server.start();
////    }

//    ros::spin();
//    return 0;
//}
