//------------------------------------------------------------------------------
//-- Matcher class
//------------------------------------------------------------------------------
//--
//--  Matches the new objects with the templates previously extracted in order to identify the object.
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

#ifndef MATCHER_H
#define MATCHER_H

#include "dataparser.h"
#include <sensor_msgs/Image.h>
#include <algorithm>

//* Matcher
/**
* Matches the new objects with the templates previously extracted in order to identify the object.
* \author Irene Sanz Nieto ( https://github.com/irenesanznieto )
* \date Feb 25th, 2014
*
*/
class Matcher
{
public:

    /*!
    * \brief Public constructor
    */
    Matcher();
    void match2D(const sensor_msgs::ImageConstPtr & msg);
    void match3D();

    int flann_comparison (cv::Mat &, float);

private:

    DataParser dataparser;  /**DataParser object that will store and load the algorithms and templates information*/
    std::vector<cv::FlannBasedMatcher> algorithms2D;

};
#endif //MATCHER_H
