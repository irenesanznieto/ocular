#ifndef FEATURE_EXTRACTOR_2D_H
#define FEATURE_EXTRACTOR_2D_H

//#include "featureextractor.h"
#include "roisegmenter2D.h"


class FeatureExtractor2D/*: public FeatureExtractor*/
{
public:

    FeatureExtractor2D();
    void extract_features(const sensor_msgs::ImageConstPtr & );

private:
    image_transport::Subscriber image_r_sub;
    image_transport::Subscriber image_l_sub;



    ros::NodeHandle nh;
    image_transport::ImageTransport it;

    void right(const sensor_msgs::ImageConstPtr & );
    void left(const sensor_msgs::ImageConstPtr & );

//    void save_descriptors(cv::Mat &descriptors, std::string filename);
//    void save_keypoints(std::vector <cv::KeyPoint> & keyp, std::string filename);

    std::string name;
};


#endif //FEATURE_EXTRACTOR_2D_H
