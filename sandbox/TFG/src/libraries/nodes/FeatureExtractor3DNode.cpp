#include "FeatureExtractor3DNode.h"

FeatureExtractor3DNode::FeatureExtractor3DNode()
{

    point_cloud_sub=nh.subscribe <sensor_msgs::PointCloud2> ("segmented_pc", 1, &FeatureExtractor3DNode::segmented_pc_cb, this);
    descriptors_pub=nh.advertise <sensor_msgs::PointCloud2> ("descriptors3D", 1);
}


void FeatureExtractor3DNode:: segmented_pc_cb (const sensor_msgs::PointCloud2ConstPtr &msg)
{
    sensor_msgs::PointCloud2 descriptors3D=fe3D.extract_features(msg);
    descriptors_pub.publish(descriptors3D);
}
