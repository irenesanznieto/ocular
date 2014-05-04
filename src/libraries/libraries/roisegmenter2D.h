//------------------------------------------------------------------------------
//-- RoiSegmenter2D class
//------------------------------------------------------------------------------
//--
//--  Segments an input image and extracts the Region Of Interest
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


#ifndef ROISEGMENTER2D_H
#define ROISEGMENTER2D_H

#include <opencv2/opencv.hpp>


//Image includes
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <ocular/HandLocPx.h>
#include <ocular/HandImage.h>

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
     * @return ocular::HandImage with the segmented image
     */
    ocular::HandImage segment(const sensor_msgs::ImageConstPtr &);

    /**
     * @brief Stores the pixel coordinates of the ROI in a private variable for its use within the class
     */
    void coordinates(const ocular::HandLocPxConstPtr &);


    /*!
    * \brief Public destructor
    */
    ~RoiSegmenter2D();

    /**
     * @brief Checks if the 2D coordinates received are inside the screen's limits.
     */
//    void checkLimits(int & , int& );
    bool checkLimits(int & , int& );


    ocular::HandLocPx getHandLocPx();

    void setHandLocPx (ocular::HandLocPx &);

    const sensor_msgs::ImageConstPtr setInputImage(std::string );


private:

    ocular::HandLocPx coord;   /**ocular::HandLocPx used to store the 2D values of the ROI */





};

#endif // ROISEGMENTER2D_H
