//------------------------------------------------------------------------------
//-- Trainer class
//------------------------------------------------------------------------------
//--
//--  Trains the algorithms for 2D and 3D recognition.
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

#ifndef TRAINER_H
#define TRAINER_H

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>


#include "dataparser.h"
#include <TFG/HandImage.h>

//* Trainer
/**
* Trains the algorithms used for 2D and 3D recognition, using new templates or stored ones.
* \author Irene Sanz Nieto ( https://github.com/irenesanznieto )
* \date Feb 25th, 2014
*
*/
class Trainer
{
public:

    /*!
    * \brief Public constructor
    * Loads the previously saved templates and trains the algorithms with them.
    */
    Trainer();


    void train2D(const sensor_msgs::ImageConstPtr &);  /** Trains a 2D algorithm with a new view of the object*/
    void train3D ();    /** Trains a 3D algorithm with a new view of the object*/

    void set_new_object(bool new_object);   /** Sets the value of the private boolean new_object*/

private:



    std::vector<cv::FlannBasedMatcher >alg2D;   /** Vector of FlannBasedMatcher algorithms, one per object */

    std::vector<std::vector<cv::Mat> >descriptors;    /** Vector that will store the descriptors dataset */

    DataParser dataparser;  /**DataParser object that will store the algorithms and templates information*/



    bool new_object;    /**Boolean that is set to true whenever the new view is of a new object*/

    int object_number();    /**Returns the index for the different vectors used in the class depending on the new_object variable*/

};

#endif //TRAINER_H
