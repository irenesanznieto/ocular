#include "roisegmenter.h"

RoiSegmenter::RoiSegmenter()
{
    point_cloud_sub= nh.subscribe <sensor_msgs::PointCloud2> ("/camera/depth_registered/points", 1, &RoiSegmenter::distance2px, this);
    coord_pub= nh.advertise <std_msgs::Int32MultiArray> ("/TFG/coord", 1);


}


void RoiSegmenter:: distance2px(const sensor_msgs::PointCloud2ConstPtr & msg)
{
    pcl::PointCloud<pcl::PointXYZRGB >::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::fromROSMsg (*msg, *cloud);

    pcl::PointXYZRGB totmax, totmin, max, min;
    pcl::getMinMax3D(*cloud, totmin, totmax);

//	ROS_INFO("Image limits:\n x : %f %f \n y : %f %f\n", totmax.x, totmin.x, totmax.y, totmin.y);
//	ROS_INFO("ROI limits:\n x : %f %f \n y : %f %f\n", max.x, min.x, max.y, min.y);

    std_msgs::Int32MultiArray coord;
    coord.data.clear();

    float distx, disty;
    distx=abs(totmax.x-totmin.x);
    disty=abs(totmax.y-totmin.y);

/*P1  _ P2
     | |
  P4 |_| P3	*/


//P1
    coord.data.push_back((int)(640*abs(min.x)/distx));	//x coordinates
    coord.data.push_back((int)(480*abs(max.y)/disty));	//y coordinates


//P3
    coord.data.push_back((int)(640*abs(max.x)/distx));	//x coordinates
    coord.data.push_back((int)(480*abs(min.y)/disty));	//y coordinates


    coord_pub.publish (coord); //publish our cloud image
}
