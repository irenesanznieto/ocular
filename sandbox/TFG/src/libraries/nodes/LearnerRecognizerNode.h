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



    void descriptors2D_cb(const TFG::HandImageConstPtr & );

    void descriptors3D_cb(const sensor_msgs::PointCloud2ConstPtr & );

    void resulting_id();

    void train3D_cb();

    void setEvent(const TFG::EventHandlerConstPtr & );


    Algorithm2D alg2D;
    Algorithm3D alg3D;


    // In these vectors, the first position will be related to 2D and the second to 3D
    int number_views2D; /** Stores the total number of views to be extracted of each object */
    int number_views3D; /** Stores the total number of views to be extracted of each object */

    int number_views_it_2D; /** Iterator that stores the current view number of the object */
    int number_views_it_3D; /** Iterator that stores the current view number of the object */

    bool learn_2D; /** Boolean that is true when the received event is learn and false otherwise*/
    bool learn_3D; /** Boolean that is true when the received event is learn and false otherwise*/

    int object_id_2D;
    int object_id_3D;

    int object_id;

    bool learning_2D;
    bool learning_3D;

};

#endif // LEARNERRECOGNIZERNODE_H
