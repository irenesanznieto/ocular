#include "RoiSegmenter3DNode.h"

RoiSegmenter3DNode::RoiSegmenter3DNode()
{
    point_cloud_sub= nh.subscribe <
        pcl::PCLPointCloud2 > ("original_pc", 1, &RoiSegmenter3DNode::point_cloud_cb, this);
    point_cloud_pub=nh.advertise <
        pcl::PCLPointCloud2 > ("segmented_pc", 1);

    coord_pub= nh.advertise <ocular::HandLocPx> ("segmented_coordinates_px", 1);

    coord_sub=nh.subscribe<ocular::HandLoc> ("hand_location", 1, &RoiSegmenter3DNode::hand_location_cb, this);

    hand=nh.subscribe<ocular::EventHandler> ("event", 1, &RoiSegmenter3DNode::hand_name_cb, this);
}


void RoiSegmenter3DNode:: hand_name_cb(const ocular::EventHandlerConstPtr & msg)
{
    roiSegmenter3D.setHandName(msg->hand);
}

void RoiSegmenter3DNode :: point_cloud_cb (const
        pcl::PCLPointCloud2ConstPtr &msg)
{
  /* pcl::PCLPointCloud2ConstPtr msg_pcl;
   pcl_conversions::toPCL(msg,msg_pcl);*/
    pcl::PCLPointCloud2  result=roiSegmenter3D.segment(msg/*_pcl*/);
    if (!result.data.empty())
        point_cloud_pub.publish(result);

}


void RoiSegmenter3DNode :: hand_location_cb (const ocular::HandLocConstPtr &msg)
{
    roiSegmenter3D.coordinates(*msg);
    coord_pub.publish(roiSegmenter3D.distance2px());

}
