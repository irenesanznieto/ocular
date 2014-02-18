#include "FeatureExtractor3DNode.h"

FeatureExtractor3DNode::FeatureExtractor3DNode()
{

    point_cloud_sub=nh.subscribe <sensor_msgs::PointCloud2> ("input_cloud", 1, &FeatureExtractor3DNode::segmented_pc_cb, this);

}


void FeatureExtractor3DNode:: segmented_pc_cb (const sensor_msgs::PointCloud2ConstPtr &msg)
{
    //complete!
}
