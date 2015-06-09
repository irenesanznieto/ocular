//------------------------------------------------------------------------------
//-- ConverterNode class
//------------------------------------------------------------------------------
//--
//--  Connects the methods implemented in the Converter class with the other packages using ROS topics.
//--
//------------------------------------------------------------------------------
//--
//-- This file belongs to the Bachelor's Thesis "In-hand object detection and tracking using 2D and 3D information"
//-- (https://github.com/irenesanznieto/ocular)
//--
//------------------------------------------------------------------------------
//-- Author: Irene Sanz Nieto
//--
//-- Released under the MIT license (more info on LICENSE.md file)
//------------------------------------------------------------------------------


#ifndef CONVERTER_NODE_H
#define CONVERTER_NODE_H

#include <ros/ros.h>
#include <skeleton_markers/Skeleton.h>
#include <ocular/HandLoc.h>

#include "../libraries/converter.h"


//* ConverterNode class
/**
* Connects the methods implemented in the Converter class with the other packages using ROS topics.
* 
* \author Irene Sanz Nieto ( https://github.com/irenesanznieto )
* \date Feb 3rd, 2014
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
    ros::Subscriber skeleton_sub;      /**Subscriber used to obtain the pi_tracker::Skeleton messages*/
    ros::Publisher hand_location_pub;      /**Publisher used to publish the resulting custom message ocular::HandLoc with the hands information*/


    Converter converterObject;       /**Object of the Converter class*/

/*!
    * \brief Callback method for the subscriber topic. 
    *
    *\param pi_tracker::SkeletonConstPtr message received through the topic
    *
    * This method stores the Skeleton message provided by the pi_tracker package and uses the Converter object to convert it to the custom message ocular::HandLoc
    */
    void converter_cb(const skeleton_markers::SkeletonConstPtr &);

};
#endif // CONVERTER_NODE_H
