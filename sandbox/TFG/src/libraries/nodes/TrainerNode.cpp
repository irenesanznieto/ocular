#include "TrainerNode.h"

TrainerNode::TrainerNode()
{
    descriptors2D=nh.subscribe<TFG::HandImage>("descriptors2D", 1, &TrainerNode::train2D_cb, this);
    //    descriptors3D=nh.subscribe("3D descriptors",1,&train3D_cb, this);

    event_sub=nh.subscribe<TFG::EventHandler>("event", 1, &TrainerNode::setEvent, this);

    number_views=10; //the total number of views to be extracted of each object
    number_views_it=0;

    //Initialize new object to true so the algorithm starts learning a NEW object
    trainer.set_new_object(true);

    //default mode: recognize
    this->learn=false;


}



void TrainerNode::train2D_cb(const TFG::HandImageConstPtr & msg)
{
    if(learn)
    {
        //        ROS_ERROR("LEARNING");

        // take each view and train the algorithm with it, until the iterator is larger than the total number of views to be taken
        if (number_views_it<number_views)
        {
            ROS_ERROR("TRAINING VIEW %d", number_views_it);

            trainer.add_descriptors(msg);
            number_views_it ++;
        }
        else if (number_views_it==number_views)
        {
            //when all the views have been taken, train the algorithm with them
            trainer.train2D();
            //when the iterator is equal to the total number of views, reset the iterator
            number_views_it=0;

            //stop the training, all the views have already been trained
            ROS_ERROR("TRAINING COMPLETED, PLEASE TAKE YOUR HAND CLOSER TO THE BODY TO START THE RECOGNITION");

        }
        else
            ROS_ERROR("Iterator of number of views greater than the total number of views");

    }
}

void TrainerNode::train3D_cb()
{

}

void TrainerNode::setEvent(const TFG::EventHandlerConstPtr & msg)
{

    if (msg->event=="learn")
    {
        //        ROS_ERROR ("LEARN EVENT RECEIVED");
        this->learn=true;

        if (msg->last_event=="recognize")   //If last event was recognize
        {
            //This is a new object to learn
            trainer.set_new_object(true);
        }
        else    //If last event was learn
        {
            trainer.set_new_object(false);  //We are still learning views of the object
        }

    }
    else if (msg->event=="recognize")   //If the event is recognize
    {
        //        ROS_ERROR ("RECOGNIZE EVENT RECEIVED");
        this->learn=false;
    }

}
