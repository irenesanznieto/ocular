//#include "RecognizerNode.h"

//RecognizerNode::RecognizerNode()
//{
//    descriptors2D_sub=nh.subscribe<ocular::HandImage>("descriptors2D", 1, &RecognizerNode::descriptors2D_cb, this);
//    object_pub=nh.advertise<std_msgs::Int32>("object_id", 1);
//    event_sub=nh.subscribe<ocular::EventHandler>("event", 1, &RecognizerNode::setEvent, this);

//    recognize=true; //the default mode is recognizer
//}


//void RecognizerNode::descriptors2D_cb(const ocular::HandImageConstPtr & msg)
//{
//    if (recognize)      //If the mode is recognize
//    {
//        int object_id;
//        //    match & publish the resulting object ID
//       object_id=alg2D.match2D(msg);

//       std::cerr<<"RECOGNIZING: OBJECT ID: "<<object_id<<std::endl;
//       object_pub.publish(object_id);
//    }
//}

//void RecognizerNode::setEvent(const ocular::EventHandlerConstPtr & msg)
//{
//    if (msg->event=="learn")
//    {
//        recognize=false;
//    }
//    else if (msg->event=="recognize")
//    {
//        recognize=true;
//    }
//}
