#ifndef FEATUREEXTRACTOR2DNODE_H
#define FEATUREEXTRACTOR2DNODE_H

#include "../libraries/featureextractor2D.h"
#include <ros/ros.h>


class FeatureExtractor2DNode
{
public:
    FeatureExtractor2DNode();

private:

    ros::NodeHandle nh;
    ros::Subscriber image_sub;
    ros::Publisher descriptors_pub;

//    ros::Publisher image_with_keypoints_pub;


    void input_image_cb (const TFG::HandImageConstPtr &);
    FeatureExtractor2D fe2D;
};

#endif // FEATUREEXTRACTOR2DNODE_H
