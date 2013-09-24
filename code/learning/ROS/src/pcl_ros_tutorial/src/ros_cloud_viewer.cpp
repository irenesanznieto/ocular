#include <ros/ros.h>
// PCL specific includes
#include <pcl/ros/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <pcl/filters/voxel_grid.h>

////////////////IT NEEDS THE ROSRUN POINT(TAB) .... EXECUTABLE THAT ACTUALLY PUBLISHES THE INPUT CLOUD!! && OF COURSE FIRST OF ALL, IT NEEDS THE 
////////////////ROSCORE PROCESS TO BE RUNNING!!

ros::Publisher pub;

void 
cloud_cb (const sensor_msgs::PointCloud2ConstPtr& cloud)
{
  sensor_msgs::PointCloud2 cloud_filtered;

  // Perform the actual filtering
  pcl::VoxelGrid<sensor_msgs::PointCloud2> sor;
  sor.setInputCloud (cloud);
  sor.setLeafSize (0.01, 0.01, 0.01);
  sor.filter (cloud_filtered);

  // Publish the data
  pub.publish (cloud_filtered);
}

int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "my_pcl_tutorial");
  ros::NodeHandle nh;

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub = nh.subscribe ("input", 1, cloud_cb);

  // Create a ROS publisher for the output point cloud
  pub = nh.advertise<sensor_msgs::PointCloud2> ("output", 1);

  // Spin
  ros::spin ();
}
