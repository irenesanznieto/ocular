//------------------------------------------------------------------------------
//-- RoiSegmenter2D class
//------------------------------------------------------------------------------
//--
//--  Segments an input image and extracts the Region Of Interest
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


#ifndef ROISEGMENTER2D_H
#define ROISEGMENTER2D_H

#include <opencv2/opencv.hpp>
#include <ros/ros.h>

//Image includes
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <TFG/HandLocPx.h>
#include <TFG/HandImage.h>

//* RoiSegmenter2D class
/**
* Segments an input image and extracts the Region Of Interest
* \author Irene Sanz Nieto ( https://github.com/irenesanznieto )
* \date Feb 3rd, 2014
*/

class RoiSegmenter2D //: public RoiSegmenter
{
public:

    /*!
    * \brief Public constructor
    */
    RoiSegmenter2D();

    /**
     * @brief Extracts the 2D ROI from the original image coming from the RGB-D sensor
     * @return TFG::HandImage with the segmented image
     */
    TFG::HandImage segment(const sensor_msgs::ImageConstPtr &);

    /**
     * @brief Stores the pixel coordinates of the ROI in a private variable for its use within the class
     */
    void coordinates(const TFG::HandLocPxConstPtr &);


    /*!
    * \brief Public destructor
    */
    ~RoiSegmenter2D();

    /**
     * @brief Checks if the 2D coordinates received are inside the screen's limits.
     */
    void checkLimits(int & , int& );


    TFG::HandLocPx getHandLocPx();


private:

    TFG::HandLocPx coord;   /**TFG::HandLocPx used to store the 2D values of the ROI */





};

#endif // ROISEGMENTER2D_H
