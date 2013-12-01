#include "roisegmenter.h"

RoiSegmenter::RoiSegmenter(): it(nh)
{
    //change this afterwards to /TFG/Handloc or something like that
    point_cloud_sub= nh.subscribe <sensor_msgs::PointCloud2> ("/camera/depth_registered/points", 1, &RoiSegmenter::segment3D, this);
    point_cloud_pub=nh.advertise <sensor_msgs::PointCloud2> ("/TFG/ROI3D", 1);

    coord_pub= nh.advertise <std_msgs::Int32MultiArray> ("/TFG/coord", 1);


//    image_sub=it.subscribe("/camera/rgb/image_color", 1, &RoiSegmenter::segment2D, this);
//    image_pub=it.advertise("/TFG/ROI2D",1);

}

void RoiSegmenter:: segment3D (const sensor_msgs::PointCloud2ConstPtr & cloud)
{
      sensor_msgs::PointCloud2 cloud_filtered;

      pcl::PassThrough<sensor_msgs::PointCloud2> pass;
      pass.setInputCloud(cloud);
      pass.setFilterFieldName("z");
      pass.setFilterLimits(0.0,1.0); // unit : meter
      pass.filter(cloud_filtered);

      pcl::PointCloud <pcl::PointXYZRGB> cloud_distance;
      pcl::fromROSMsg(cloud_filtered, cloud_distance);
      RoiSegmenter::distance2px(cloud_distance);

     //publish ROI 3D
    point_cloud_pub.publish(cloud_filtered);
}

void RoiSegmenter:: segment2D (const sensor_msgs::ImageConstPtr & msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    cv::Point first=cv::Point(coord.data.at(0),coord.data.at(1));
    cv::Point second=cv::Point(coord.data.at(1),coord.data.at(2));

    cv::Rect myROI(first.x, first.y, second.x, second.y);
    cv::Mat croppedImage = cv_ptr->image(myROI);

    imshow("CROPPED IMAGE", croppedImage);
    cv::waitKey(3);

    croppedImage.copyTo(cv_ptr->image);
    image_pub.publish(cv_ptr->toImageMsg());
}

void RoiSegmenter:: distance2px( pcl::PointCloud <pcl::PointXYZRGB> cloud)
{
    pcl::PointXYZRGB totmax, totmin, max, min;
    pcl::getMinMax3D(cloud, totmin, totmax);

//	ROS_INFO("Image limits:\n x : %f %f \n y : %f %f\n", totmax.x, totmin.x, totmax.y, totmin.y);
//	ROS_INFO("ROI limits:\n x : %f %f \n y : %f %f\n", max.x, min.x, max.y, min.y);

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
