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


        pcl::PointCloud <pcl::PointXYZ> output_cloud;
        pcl::fromROSMsg(cloud_filtered, output_cloud);

        pcl::PointCloud <pcl::PointXYZ> input_cloud;
        pcl::fromROSMsg(*cloud_sor_ptr, input_cloud);

        RoiSegmenter3D::distance2px(input_cloud, output_cloud);
    }

    //publish ROI 3D
    point_cloud_pub.publish(cloud_filtered);

}



void RoiSegmenter3D:: distance2px(pcl::PointCloud<pcl::PointXYZ>& cloud, pcl::PointCloud <pcl::PointXYZ>& output_cloud)
{
    pcl::PointXYZ totmax, totmin, max, min;
    pcl::getMinMax3D(cloud, totmin, totmax);
    pcl::getMinMax3D(output_cloud, min, max);

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

    int multx, multy;
    float r=disty/distx;
    if (distx>disty)
    {
        multx=640/distx;
        multy=480/(r*disty);
    }
    else
    {
        multy=640/disty;
        multx=480*r/distx;
    }


    float offx=0, offy=0;


    offx=abs(totmin.x-min.x);
    offy=abs(totmax.y-max.y);

    //P1
    coord.data.push_back((int)( multx*(abs(min.x)+ offx) ));	//x coordinates
    coord.data.push_back((int)( multy*(abs(max.y)+ offy) ));	//y coordinates


    offx=abs(totmax.x-max.x);
    offy=abs(totmin.y-min.y);

    //P3
    coord.data.push_back((int)( multx*(abs(max.x)+ offx) ));	//x coordinates
    coord.data.push_back((int)( multy*(abs(min.y)+ offy) ));	//y coordinates

    if (coord.data[0]>0 && coord.data[1]>0 && coord.data[2]>0 && coord.data[3]>0)
        coord_pub.publish (coord); //publish our cloud image
}

void RoiSegmenter3D::coordinates (const TFG::HandLocConstPtr & msg)
{
    coord=*msg;
}
