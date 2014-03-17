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

    int number_views; /** Stores the total number of views to be extracted of each object */
    int number_views_it; /** Iterator that stores the current view number of the object */
    bool training_completed; /** Boolean that is true when the training has been completed */

};

#endif // TRAINERNODE_H
