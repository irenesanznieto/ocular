#include "featureextractor2D.h"

FeatureExtractor2D::FeatureExtractor2D()
{}

TFG::HandImage FeatureExtractor2D::extract_features(const TFG::HandImageConstPtr & msg)
{
    TFG::HandImage result;
    result.image.resize(2);
    result.name.resize(2);

    cv_bridge::CvImagePtr cv_ptr, final_ptr;
    for (unsigned int i=0; i<msg->image.size();i++)
    {
        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg->image[i], sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
        }

        cv::Mat  gimage;
        cvtColor(cv_ptr->image, gimage, CV_BGR2GRAY);

        cv::Mat mask;

        std::vector <cv::KeyPoint> keypoints;
        cv::Mat descriptors;
        cv::ORB orb;

        orb(gimage, mask,  keypoints, descriptors);


        final_ptr->image=descriptors.clone();

        //fill the result of the feature extraction:
        result.image.push_back( *final_ptr->toImageMsg());
        result.name[i]=msg->name[i];


//            Draw circles in the keypoints
            for (unsigned int i=0; i<keypoints.size(); i++)
            {
                circle(cv_ptr->image, keypoints[i].pt, keypoints[i].size, cv::Scalar(0,0,255), 1);
            }

            this->image_with_keypoints.data=cv_ptr->image.clone();
    }
    return result;
}

sensor_msgs::Image FeatureExtractor2D:: get_image_with_keypoints()
{
    return this->image_with_keypoints;
}

