#include "TrainerNode.h"

TrainerNode::TrainerNode()
{
    descriptors2D=nh.subscribe<TFG::HandImage>("descriptors_2D", 1, &TrainerNode::train2D_cb, this);
    //    descriptors3D=nh.subscribe("3D descriptors",1,&train3D_cb, this);

    event_sub=nh.subscribe<TFG::EventHandler>("event", 1, &TrainerNode::setEvent, this);

    number_views=1; //the total number of views to be extracted of each object
}



void TrainerNode::train2D_cb(const TFG::HandImageConstPtr & msg)
{
    int i=0;

    while (i<number_views)
    {
    trainer.train2D(msg);
    i ++;
    }

}

void TrainerNode::train3D_cb()
{

}

void TrainerNode::setEvent(const TFG::EventHandlerConstPtr & msg)
{
    if (msg->event=="learn")
    {
        trainer.set_start_training(true);

        if (msg->last_event=="recognize")
        {
            //This is a new object to learn
            trainer.set_new_object(true);

        }
        else
            trainer.set_new_object(false);  //We are still learning views of the object

    }
    else if (msg->event=="recognize")
    {
        trainer.set_start_training(false);
    }

}
