#ifndef CONVERTER_NODE_H
#define CONVERTER_NODE_H

#include <ros/ros.h>
#include <pi_tracker/Skeleton.h>
#include <TFG/HandLoc.h>

#include "../libraries/converter.h"


//* ConverterNode class
/**
 * This class connects the methods implemented in the Converter class with the other packages through ROS nodes. 
 * 
*  
*/

class ConverterNode
{
public:

/*!
    * \brief Public constructor
    *
    * Initializes the ros::Subscriber and ros::Publisher nodes. The topics specified in there are used as variables that are changed in the launch file
    */
    ConverterNode();

private:


    ros::NodeHandle nh;             /** NodeHandle variable to control the nodes*/
    ros::Subscriber input_sub;      /**Subscriber used to obtain the pi_tracker::Skeleton messages*/
    ros::Publisher output_sub;      /**Publisher used to publish the resulting custom message TFG::HandLoc with the hands information*/


    Converter converterObject;       /**Object of the Converter class*/

/*!
    * \brief Callback method for the subscriber topic. 
    *
    *\param pi_tracker::SkeletonConstPtr message received through the topic
    *
    * This method stores the Skeleton message provided by the pi_tracker package and uses the Converter object to convert it to the custom message TFG::HandLoc
    */
    void converter_cb(const pi_tracker::SkeletonConstPtr &);

};
#endif // CONVERTER_NODE_H
