//------------------------------------------------------------------------------
//-- Algorithm2D class
//------------------------------------------------------------------------------
//--
//--  Trains the algorithm for 2D recognition and matches the new information with the trained one.
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

#ifndef ALGORITHM2D_H
#define ALGORITHM2D_H

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>


#include "dataparser.h"
#include <TFG/HandImage.h>

//* Algorithm2D
/**
* Trains the algorithm for 2D recognition and matches the new information with the trained one.
* \author Irene Sanz Nieto ( https://github.com/irenesanznieto )
* \date Feb 25th, 2014
*
*/
class Algorithm2D
{
public:

    /*!
    * \brief Public constructor
    * Loads the previously saved templates and trains the algorithms with them.
    */
    Algorithm2D();

    ~Algorithm2D();


//    void train3D ();    /** Trains a 3D algorithm with a new view of the object*/

    void set_new_object(bool new_object);   /** Sets the value of the private boolean new_object*/

    void add_descriptors(const TFG::HandImageConstPtr &, int number_view);

    int match2D(const TFG::HandImageConstPtr & msg);



private:

    std::vector<cv::FlannBasedMatcher >alg2D;   /** Vector of FlannBasedMatcher algorithms, one per object */

    std::vector<std::vector<cv::Mat> >descriptors;    /** Vector that will store the descriptors dataset */

    DataParser dataparser;  /**DataParser object that will store and load the algorithms and templates information*/

    int flann_comparison (cv::Mat , float);


    bool new_object;    /**Boolean that is set to true whenever the new view is of a new object*/

    int object_number;

    int matched_object_id;  /** Number that represents the object being matched by the algorithm. **/

    int matched_object_ratio;  /** Number that represents the ratio obtained by the recognized object**/

};

#endif //ALGORITHM2D_H
