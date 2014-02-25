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
    void match();
    std::vector <cv::DMatch> flann_comparison (cv::Mat  &, 	cv::Mat  &, float &, float);

private:
    void match2D();

    DataParser dataparser;

};
#endif //MATCHER_H
