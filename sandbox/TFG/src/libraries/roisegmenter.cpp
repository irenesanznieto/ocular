#include "roisegmenter.h"

//RoiSegmenter::RoiSegmenter(): it_(nh_)
//{
//    sub_node="/camera/depth_registered/points";
//    point_cloud_sub_ = it_.subscribe(sub_node, 1, &RoiSegmenter2D::distance2px, this);

//    pub_node="/TFG/coord";
//    coord_pub_ = it_.advertise<std_msgs::Int32MultiArray> (pub_node, 1);


//}



//void RoiSegmenter:: distance2px(pcl::PointCloud<PointT>::Ptr cloud)
//{
//    PointT totmax, totmin, max, min;
//    pcl::getMinMax3D(*cloud, totmin, totmax);
//    pcl::getMinMax3D(*output_cloud, min, max);

////	ROS_INFO("Image limits:\n x : %f %f \n y : %f %f\n", totmax.x, totmin.x, totmax.y, totmin.y);
////	ROS_INFO("ROI limits:\n x : %f %f \n y : %f %f\n", max.x, min.x, max.y, min.y);

//    std_msgs::Int32MultiArray coord;
//    coord.data.clear();

//    float distx, disty;
//    distx=abs(totmax.x-totmin.x);
//    disty=abs(totmax.y-totmin.y);

///*P1  _ P2
//     | |
//  P4 |_| P3	*/


////P1
//    coord.data.push_back((int)(640*abs(min.x)/distx));	//x coordinates
//    coord.data.push_back((int)(480*abs(max.y)/disty));	//y coordinates


////P3
//    coord.data.push_back((int)(640*abs(max.x)/distx));	//x coordinates
//    coord.data.push_back((int)(480*abs(min.y)/disty));	//y coordinates


//    coord_pub_.publish (coord); //publish our cloud image
//}
