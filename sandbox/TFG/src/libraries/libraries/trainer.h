#ifndef TRAINER_H
#define TRAINER_H
#include <opencv2/opencv.hpp>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>

class Trainer
{
public:

    Trainer();
    void train(const sensor_msgs::PointCloud2ConstPtr & , const sensor_msgs::ImageConstPtr & );

private:

    void train2D(cv::FlannBasedMatcher &alg2D);

    cv::FlannBasedMatcher alg2D;

    void save_template();
    void save_algorithm();

};

#endif //TRAINER_H
