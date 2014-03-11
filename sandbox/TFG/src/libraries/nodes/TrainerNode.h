#ifndef TRAINERNODE_H
#define TRAINERNODE_H

#include "../libraries/trainer.h"
#include <ros/ros.h>
#include <TFG/EventHandler.h>

class TrainerNode
{
public:
    TrainerNode();

private:

    ros::NodeHandle nh;
    ros::Subscriber descriptors2D;
    ros::Subscriber descriptors3D;

    ros::Subscriber event_sub;


    void train2D_cb(const TFG::HandImageConstPtr & );

    void train3D_cb();

    void setEvent(const TFG::EventHandlerConstPtr & );


    Trainer trainer;

};

#endif // TRAINERNODE_H
