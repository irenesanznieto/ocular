#include "roisegmenter3D.h"

RoiSegmenter3D::RoiSegmenter3D()
{
    point_cloud_sub= nh.subscribe <sensor_msgs::PointCloud2> ("input", 1, &RoiSegmenter3D::segment, this);
    point_cloud_pub=nh.advertise <sensor_msgs::PointCloud2> ("output_cloud", 1);

    coord_pub= nh.advertise <std_msgs::Int32MultiArray> ("output_coord", 1);
    coord_sub=nh.subscribe<TFG::HandLoc> ("input_coord", 1, &RoiSegmenter3D::coordinates, this);


}

void RoiSegmenter3D:: segment (const sensor_msgs::PointCloud2ConstPtr & /*cloud*/ cloud_sor_ptr)
{
    sensor_msgs::PointCloud2 cloud_filtered;
//    sensor_msgs::PointCloud2  cloud_sor;

//    //Statistical outlier removal
//    pcl::StatisticalOutlierRemoval<sensor_msgs::PointCloud2> sor;
//    sor.setInputCloud (cloud);
//    sor.setMeanK (50);
//    sor.setStddevMulThresh (1.0);
//    sor.filter(cloud_sor);

//    //Make pointer of the cloud_sor point cloud
//    const sensor_msgs::PointCloud2ConstPtr& cloud_sor_ptr = boost::make_shared<sensor_msgs::PointCloud2>(cloud_sor);

    //make 3 passThrough filters, one for each coordinate
    pcl::PassThrough<sensor_msgs::PointCloud2> x, y, z;

    //set input cloud
    x.setInputCloud(cloud_sor_ptr);
    y.setInputCloud(cloud_sor_ptr);
    z.setInputCloud(cloud_sor_ptr);

    double halfx=0.1;
    double halfy=0.1;
    double halfz=0.05;

    for (unsigned int i=0; i<coord.position.size(); i++)
    {
        float xcenter= coord.position[i].x;
        float ycenter=coord.position[i].y;
        float zcenter=coord.position[i].z;


        //set limits  --> assuming the obtained position is the center, filter a cube
        x.setFilterFieldName("x");
        x.setFilterLimits(xcenter-halfx,xcenter+halfx); // unit : meter
        y.setFilterFieldName("y");
        y.setFilterLimits(ycenter-halfy,ycenter+halfy); // unit : meter
        z.setFilterFieldName("z");
        z.setFilterLimits(zcenter-halfz,zcenter+halfz); // unit : meter

        //filter
        x.filter(cloud_filtered);
        y.filter(cloud_filtered);
        z.filter(cloud_filtered);


        pcl::PointCloud <pcl::PointXYZ> cloud_distance;
        pcl::fromROSMsg(cloud_filtered, cloud_distance);

        RoiSegmenter3D::distance2px(cloud_distance);
    }
    //publish ROI 3D
    point_cloud_pub.publish(cloud_filtered);

}



void RoiSegmenter3D:: distance2px(pcl::PointCloud <pcl::PointXYZ> cloud)
{
    pcl::PointXYZ totmax, totmin, max, min;
    pcl::getMinMax3D(cloud, totmin, totmax);

//    ROS_ERROR("Image limits:\n x : %f %f \n y : %f %f\n", totmax.x, totmin.x, totmax.y, totmin.y);
//    ROS_ERROR("ROI limits:\n x : %f %f \n y : %f %f\n", max.x, min.x, max.y, min.y);

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

void RoiSegmenter3D::coordinates (const TFG::HandLocConstPtr & msg)
{
    coord=*msg;
}
