#ifndef CONVERTER_H
#define CONVERTER_H
#include <ros/ros.h>
#include <pi_tracker/Skeleton.h>
#include <TFG/HandLoc.h>
#include <std_msgs/String.h>

//* Converter
/**
* This class is used as a bridge between the software used to locate the hand's position (in this case, the ROS package pi_tracker) and the project. 
* From the pi_tracker::Skeleton message, it fills the TFG::HandLoc message. 
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
    TFG::HandLoc handCoordinatesExtractor(const pi_tracker::Skeleton & msg);

};
#endif // CONVERTER_H
