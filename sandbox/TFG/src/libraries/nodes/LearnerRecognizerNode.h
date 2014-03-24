#ifndef LEARNERRECOGNIZERNODE_H
#define LEARNERRECOGNIZERNODE_H

#include "../libraries/algorithm2D.h"
#include "../libraries/algorithm3D.h"
#include <std_msgs/Int32.h>

#include <ros/ros.h>
#include <TFG/EventHandler.h>

class LearnerRecognizerNode
{
public:
    LearnerRecognizerNode();

private:

    ros::NodeHandle nh;
    ros::Subscriber descriptors2D;
    ros::Subscriber descriptors3D;

    ros::Subscriber event_sub;

    ros::Publisher object_pub;



    void descriptors_cb(const TFG::HandImageConstPtr & );

    void train3D_cb();

    void setEvent(const TFG::EventHandlerConstPtr & );


    Algorithm2D alg2D;

    int number_views; /** Stores the total number of views to be extracted of each object */
    int number_views_it; /** Iterator that stores the current view number of the object */
    bool learn; /** Boolean that is true when the received event is learn and false otherwise*/
};

#endif // LEARNERRECOGNIZERNODE_H
