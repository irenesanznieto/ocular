#include "LearnerRecognizerNode.h"

LearnerRecognizerNode::LearnerRecognizerNode()
{
    object_pub=nh.advertise<std_msgs::Int32>("object_id", 1);

    descriptors2D=nh.subscribe<TFG::HandImage>("descriptors2D", 1, &LearnerRecognizerNode::descriptors_cb, this);
    //    descriptors3D=nh.subscribe("3D descriptors",1,&train3D_cb, this);

    event_sub=nh.subscribe<TFG::EventHandler>("event", 1, &LearnerRecognizerNode::setEvent, this);

    number_views=5; //the total number of views to be extracted of each object
    alg2D.set_number_views(this->number_views); //pass the number of views to the algorithm 2D

    number_views_it=0;

    //Initialize new object to true so the algorithm starts learning a NEW object
//    alg2D.set_new_object(true);

    //default mode: recognize
    this->learn=false;
}


void LearnerRecognizerNode::setEvent(const TFG::EventHandlerConstPtr & msg)
{
        if (msg->event=="learn")
        {
            if (msg->last_event=="recognize")   //If last event was recognize
            {
                this->learn=true;
                //This is a new object to learn
                alg2D.set_new_object(true);
            }
//            else if (msg->last_event!="recognize" && this->learn==false)   //If last event was learn
//            {
//                this->learn=true;
//                alg2D.set_new_object(true);  //We are still learning views of the object
//            }
            else
            {
                alg2D.set_new_object(false);  //We are still learning views of the object
            }

        }
        else if (msg->event=="recognize")   //If the event is recognize
        {
            if (number_views_it<number_views)   //If the learning is still in process, carry on learning
            {
                this->learn=true;
            }
            else
            {
                this->learn=false;
            }
        }
}


void LearnerRecognizerNode::descriptors_cb(const TFG::HandImageConstPtr & msg)
{
    if(this->learn)
    {
        // take each view and train the algorithm with it, until the iterator is larger than the total number of views to be taken
        if (number_views_it<number_views)
        {
            std::cerr<<"TRAINING VIEW "<< number_views_it<<std::endl;
            alg2D.add_descriptors(msg, number_views_it);
            number_views_it ++;
            sleep(1);

        }
        else if (number_views_it==number_views)
        {
            //when the iterator is equal to the total number of views, reset the iterator
            number_views_it=0;

            //stop the learning until a new recognize - learn events happen
            this->learn=false;

            //stop the training, all the views have already been trained
            std::cerr<<"TRAINING COMPLETED, PLEASE TAKE YOUR HAND CLOSER TO THE BODY TO START THE RECOGNITION"<<std::endl;

        }
        else
            std::cerr<<"Iterator of number of views greater than the total number of views"<<std::endl;
    }


    else if (!this->learn)      //If the mode is recognize
    {
        int object_id;
        //    match & publish the resulting object ID
        object_id=alg2D.match2D(msg);

        object_pub.publish(object_id);
    }
}
