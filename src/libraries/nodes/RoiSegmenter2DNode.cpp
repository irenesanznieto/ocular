#include "RoiSegmenter2DNode.h"

RoiSegmenter2DNode::RoiSegmenter2DNode(): it(nh)
{
    coord_sub=nh.subscribe <ocular::HandLocPx>("segmented_coordinates_px", 1, &RoiSegmenter2DNode::hand_coordinates_2D_cb, this);
    image_sub=it.subscribe("original_image", 1, &RoiSegmenter2DNode::original_image_cb, this);
    hands_images_pub=nh.advertise<ocular::HandImage>("segmented_image",1);
}


void RoiSegmenter2DNode::hand_coordinates_2D_cb(const ocular::HandLocPxConstPtr &msg)
{
    roiSegmenter2D.coordinates(msg);
}


void RoiSegmenter2DNode::original_image_cb(const sensor_msgs::ImageConstPtr &msg)
{
    ocular::HandImage result=roiSegmenter2D.segment(msg);

    if (!result.image.empty())
        hands_images_pub.publish(result);
}
