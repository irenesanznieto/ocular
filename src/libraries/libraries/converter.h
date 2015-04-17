//------------------------------------------------------------------------------
//-- Converter class
//------------------------------------------------------------------------------
//--
//--  Bridge between the software used to locate the hand's position (in this case, the ROS package pi_tracker) and the project. 
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

#ifndef CONVERTER_H
#define CONVERTER_H
#include <ros/ros.h>
#include <skeleton_markers/Skeleton.h>
#include <ocular/HandLoc.h>
#include <std_msgs/String.h>

//* Converter
/**
* Bridge between the software used to locate the hand's position (in this case, the ROS package pi_tracker) and the project. 
* From the pi_tracker::Skeleton message, it fills the ocular::HandLoc message. 
* \author Irene Sanz Nieto ( https://github.com/irenesanznieto )
* \date Feb 3rd, 2014
*   
*/

class Converter 
{
    
public:

    /*!
    * \brief Public constructor
    */
    Converter();
    
    /*!
    * \brief Method that extracts the hands information from the pi_tracker::Skeleton message
    *
    * This description is displayed lower in the doxygen as an extended description along with
    * the above brief description.
    * \param msg       The pi_tracker::Skeleton message provided by the ROS package pi_tracker
    */
    ocular::HandLoc handCoordinatesExtractor(const skeleton_markers::Skeleton & msg);

};
#endif // CONVERTER_H
