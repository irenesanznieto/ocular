//------------------------------------------------------------------------------
//-- RoiSegmenter2DNode class 
//------------------------------------------------------------------------------
//--
//--  Connects the methods implemented in the RoiSegmenter2D class with the other packages using ROS topics.
//--
//------------------------------------------------------------------------------
//--
//-- This file belongs to the Bachelor's Thesis "In-hand object detection and tracking using 2D and 3D information"
//-- (https://github.com/irenesanznieto/TFG)
//--
//------------------------------------------------------------------------------
//-- Author: Irene Sanz Nieto
//--
//-- Released under the MIT license (more info on LICENSE.md file)
//------------------------------------------------------------------------------

#ifndef ROISEGMENTER2DNODE_H
#define ROISEGMENTER2DNODE_H

#include "../libraries/roisegmenter2D.h"

//* RoiSegmenter2DNode class
/**
* Connects the methods implemented in the RoiSegmenter2D class with the other packages using ROS topics.
* \author Irene Sanz Nieto ( https://github.com/irenesanznieto )
* \date Feb 3rd, 2014
*/
class RoiSegmenter2DNode
{
public:

    /*!
    * \brief Public constructor
    *
    * Initializes the ros::Subscriber and ros::Publisher nodes. The topics specified in there are used as variables that are changed in the launch file
    */
    RoiSegmenter2DNode();


private:

    ros::NodeHandle nh;     /** NodeHandle variable to control the nodes*/
    image_transport::ImageTransport it;     /** Image transport variable*/

    ros::Publisher hands_images_pub;    /** Publisher that publishes both the left and right hand ROI images */

    image_transport::Subscriber image_sub;  /** Subscriber used to obtain the original 2D image from the RGB-D sensor*/
    ros::Subscriber coord_sub;      /** Subscriber used to obtain the 2D hands coordinates (in pixels)*/

    RoiSegmenter2D roiSegmenter2D;  /** Object of the RoiSegmenter2D class*/


    /**
     * @brief Callback function that stores the 2D ROI coordinates.
     */
    void hand_coordinates_2D_cb(const TFG::HandLocPxConstPtr &);

    /**
     * @brief Callback function that passes the original image from the RGB-D sensor to a RoiSegmenter2D function in order to crop the 2D ROI for both hands
     */
    void original_image_cb(const sensor_msgs::ImageConstPtr &);


};

#endif // ROISEGMENTER2DNODE_H
