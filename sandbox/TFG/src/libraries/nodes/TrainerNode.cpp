#include "TrainerNode.h"

TrainerNode::TrainerNode()
{
    descriptors2D=nh.subscribe<TFG::HandImage>("descriptors_2D", 1, &TrainerNode::train2D_cb, this);
    //    descriptors3D=nh.subscribe("3D descriptors",1,&train3D_cb, this);

    event_sub=nh.subscribe<TFG::EventHandler>("event", 1, &TrainerNode::setEvent, this);
}



void TrainerNode::train2D_cb(const TFG::HandImageConstPtr & msg)
{
    trainer.train2D(msg);
}

void TrainerNode::train3D_cb()
{

}

void TrainerNode::setEvent(const TFG::EventHandlerConstPtr & msg)
{
    if (msg->event=="learn")
        trainer.set_start_training(true);

    else if (msg->event=="recognize")
        trainer.set_start_training(false);
}
