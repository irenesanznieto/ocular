#include "FeatureExtractor3DNode.h"

FeatureExtractor3DNode::FeatureExtractor3DNode()
{
    point_cloud_sub=nh.subscribe <sensor_msgs::PointCloud2> ("segmented_pc", 1, &FeatureExtractor3DNode::segmented_pc_cb, this);
    descriptors_pub=nh.advertise <sensor_msgs::PointCloud2> ("descriptors3D", 1);
}


void FeatureExtractor3DNode:: segmented_pc_cb (const sensor_msgs::PointCloud2ConstPtr &msg_ptr)
{
    sensor_msgs::PointCloud2 msg=*msg_ptr;
    pcl::PCLPointCloud2 msg_pcl;
    pcl_conversions::toPCL(msg, msg_pcl);

    const pcl::PCLPointCloud2ConstPtr& msg_pcl_ptr=boost::make_shared<pcl::PCLPointCloud2>(msg_pcl);

    pcl::PCLPointCloud2 result=fe3D.extract_features("pfh", msg_pcl_ptr);

    sensor_msgs::PointCloud2 result_out;
    pcl_conversions::fromPCL(result, result_out);
    descriptors_pub.publish(result_out);
}
