#include "TrainerNode.h"

TrainerNode::TrainerNode()
{
    descriptors2D=nh.subscribe<TFG::HandImage>("2D descriptors", 1, &train2D_cb, this);
    descriptors3D=nh.subscribe("3D descriptors",1,&train3D_cb, this);
}



void TrainerNode::train2D_cb(const TFG::HandImageConstPtr & msg)
{

    // be careful!! till here we're working with the two hands... what should we do now?? only train with one hand...???
//    trainer.train2D(msg);
}

void TrainerNode::train3D_cb()
{

}
