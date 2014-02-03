#include "RoiSegmenter2DNode.h"

RoiSegmenter2DNode::RoiSegmenter2DNode(): it(nh)
{
    coord_sub=nh.subscribe <TFG::HandLocPx>("input_coord", 1, &RoiSegmenter2DNode::hand_coordinates_2D_cb, this);
    image_sub=it.subscribe("input", 1, &RoiSegmenter2DNode::original_image_cb, this);
    hands_images_pub=nh.advertise<TFG::HandImage>("output",1);
}


void RoiSegmenter2DNode::hand_coordinates_2D_cb(const TFG::HandLocPxConstPtr &msg)
{
    roiSegmenter2D.coordinates(msg);
}


void RoiSegmenter2DNode::original_image_cb(const sensor_msgs::ImageConstPtr &msg)
{
    hands_images_pub.publish(roiSegmenter2D.segment(msg));
}
