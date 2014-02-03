#include "RoiSegmenter3DNode.h"

RoiSegmenter3DNode::RoiSegmenter3DNode()
{
    point_cloud_sub= nh.subscribe <sensor_msgs::PointCloud2> ("input", 1, &RoiSegmenter3DNode::point_cloud_cb, this);
    point_cloud_pub=nh.advertise <sensor_msgs::PointCloud2> ("output_cloud", 1);

    coord_pub= nh.advertise <TFG::HandLocPx> ("output_coord", 1);

    coord_sub=nh.subscribe<TFG::HandLoc> ("input_coord", 1, &RoiSegmenter3DNode::hand_location_cb, this);
}


void RoiSegmenter3DNode :: point_cloud_cb (const sensor_msgs::PointCloud2ConstPtr &msg)
{
    point_cloud_pub.publish(roiSegmenter3D.segment(msg));

}


void RoiSegmenter3DNode :: hand_location_cb (const TFG::HandLocConstPtr &msg)
{
    roiSegmenter3D.coordinates(msg);
    coord_pub.publish(roiSegmenter3D.distance2px());

}
