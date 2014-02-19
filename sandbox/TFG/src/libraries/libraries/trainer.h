#ifndef TRAINER_H
#define TRAINER_H

#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <fstream>

class Trainer
{
public:

    Trainer();
    void train(const sensor_msgs::ImageConstPtr & descriptors);

    void set_new_object(bool new_object);

    void getTemplates ();


private:

    std::vector <std::string> get_file_names (std::string );

    void train2D(cv::Mat);

    std::vector<cv::FlannBasedMatcher >alg2D;

    std::vector<std::vector<cv::Mat> >descriptors;    /** Vector that will store the descriptors dataset */


    void save_template_2D();
    void save_algorithm_2D();


    bool new_object;


    cv::Mat load_descriptor (std::string );

};

#endif //TRAINER_H
