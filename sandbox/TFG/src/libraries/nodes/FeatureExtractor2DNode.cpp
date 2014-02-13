#include "FeatureExtractor2DNode.h"

FeatureExtractor2DNode::FeatureExtractor2DNode()/*: it(nh)*/
{
    image_sub=/*it.*/nh.subscribe<TFG::HandImage>("input_image", 1, &FeatureExtractor2D::input_image_cb, this);
}

void FeatureExtractor2DNode::input_image_cb (const TFG::HandImageConstPtr &msg)
{
    fe2D.extract_features(msg);
}
