#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
 // PCL specific includes
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/visualization/cloud_viewer.h>


int
main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

  // Fill in the cloud data
  pcl::PCDReader reader;
  // Replace the path below with the path where you saved your file
  reader.read<pcl::PointXYZ> ("src/pcl_ros_tutorial/data/table_scene_lms400.pcd", *cloud); //reading from main directory (ROS)

	pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
  	 viewer.showCloud(cloud);
   	while (!viewer.wasStopped())
   	{
   	}

  return (0);
}
