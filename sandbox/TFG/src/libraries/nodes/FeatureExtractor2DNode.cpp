#include "FeatureExtractor2DNode.h"

FeatureExtractor2DNode::FeatureExtractor2DNode()
{
    image_sub=nh.subscribe<TFG::HandImage>("segmented_image", 1, &FeatureExtractor2DNode::input_image_cb, this);
    descriptors_pub=nh.advertise<TFG::HandImage>("descriptors2D", 1);

//    image_with_keypoints_pub=nh.advertise<TFG::HandImage>("image_with_keypoints", 1);
}

void FeatureExtractor2DNode::input_image_cb (const TFG::HandImageConstPtr &msg)
{
    descriptors_pub.publish(fe2D.extract_features(msg));
//    image_with_keypoints_pub.publish(fe2D.get_image_with_keypoints());
}
