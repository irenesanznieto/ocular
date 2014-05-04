#ifndef FEATUREEXTRACTOR2DNODE_H
#define FEATUREEXTRACTOR2DNODE_H

#include "../libraries/featureextractor2D.h"
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

class FeatureExtractor2DNode
{
public:
    FeatureExtractor2DNode();

private:

    ros::NodeHandle nh;
    ros::Subscriber image_sub;
    ros::Publisher descriptors_pub;

    image_transport::Publisher image_with_keypoints_pub;
    image_transport::ImageTransport it;

    void input_image_cb (const ocular::HandImageConstPtr &);
    FeatureExtractor2D fe2D;
};

#endif // FEATUREEXTRACTOR2DNODE_H
