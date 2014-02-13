#ifndef FEATUREEXTRACTOR2DNODE_H
#define FEATUREEXTRACTOR2DNODE_H
#include "../libraries/featureextractor2D.h"

class FeatureExtractor2DNode
{
public:
    FeatureExtractor2DNode();

private:
//    image_transport::Subscriber image_sub;

    ros::NodeHandle nh;
    ros::Subscriber image_sub;
//    image_transport::ImageTransport it;

    void input_image_cb (const TFG::HandImageConstPtr &);
    FeatureExtractor2D fe2D;
};

#endif // FEATUREEXTRACTOR2DNODE_H
