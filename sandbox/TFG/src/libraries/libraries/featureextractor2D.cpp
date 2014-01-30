#include "featureextractor2D.h"

FeatureExtractor2D::FeatureExtractor2D(): it(nh)
{
    image_r_sub=it.subscribe("input_r_image", 1, &FeatureExtractor2D::right, this);
    image_l_sub=it.subscribe("input_l_image", 1, &FeatureExtractor2D::left, this);

}

void FeatureExtractor2D::right(const sensor_msgs::ImageConstPtr & msg)
{
    this->name="right";
    this->extract_features(msg);
}

void FeatureExtractor2D::left(const sensor_msgs::ImageConstPtr & msg)
{
    this->name="left";
    this->extract_features(msg);
}


void FeatureExtractor2D::extract_features(const sensor_msgs::ImageConstPtr & msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }


    cv::Mat  gimage;
    cvtColor(cv_ptr->image, gimage, CV_BGR2GRAY);

    cv::Mat mask;

    std::vector <cv::KeyPoint> keypoints;
    cv::Mat descriptors;
    cv::ORB orb;
	
    orb(gimage, mask,  keypoints, descriptors);
	
//    Draw circles in the keypoints
//    for (unsigned int i=0; i<keypoints.size(); i++)
//    {
//        circle(cv_ptr->image, keypoints[i].pt, keypoints[i].size, cv::Scalar(0,0,255), 1);
//    }

//    cv::imshow("ORB DESCRIPTORS", cv_ptr->image);
//    cv::waitKey(10);

}


//void FeatureExtractor2D:: save_descriptors(cv::Mat &descriptors, std::string filename)
//{
//    filename+= "_d.yml";
//    cv::FileStorage fs(filename, cv::FileStorage::WRITE);
//    fs <<"descriptors"<< descriptors;
//}

//void FeatureExtractor2D:: save_keypoints(std::vector <cv::KeyPoint> & keyp, std::string filename)
//{
//    filename+= "_k.yml";
//    cv::FileStorage fs(filename, cv::FileStorage::WRITE);
//    fs <<"keypoints"<< keyp;
//}
