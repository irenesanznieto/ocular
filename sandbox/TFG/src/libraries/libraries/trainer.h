#ifndef TRAINER_H
#define TRAINER_H

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>


#include "dataparser.h"

class Trainer
{
public:

    Trainer();
    void train(const sensor_msgs::ImageConstPtr & descriptors);

    void set_new_object(bool new_object);

    void getTemplates ();


private:


    void train2D(cv::Mat);

    std::vector<cv::FlannBasedMatcher >alg2D;

    std::vector<std::vector<cv::Mat> >descriptors;    /** Vector that will store the descriptors dataset */

    DataParser dataparser;



    bool new_object;


};

#endif //TRAINER_H
