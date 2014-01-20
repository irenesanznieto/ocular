#include "roisegmenter3D.h"

RoiSegmenter3D::RoiSegmenter3D()
{
    point_cloud_sub= nh.subscribe <sensor_msgs::PointCloud2> ("input", 1, &RoiSegmenter3D::segment, this);
    point_cloud_pub=nh.advertise <sensor_msgs::PointCloud2> ("output_cloud", 1);

    coord_r_pub= nh.advertise <std_msgs::Int32MultiArray> ("output_r_coord", 1);
    coord_l_pub= nh.advertise <std_msgs::Int32MultiArray> ("output_l_coord", 1);

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


    //TODO: put this as a function of the distance to the kinect
    double halfx=0.05;
    double halfy=0.05;
    double halfz=0.03;


    for (unsigned int i=0; i<coord.position.size(); i++)
    {

        float xcenter= coord.position[i].x;
        float ycenter=coord.position[i].y;
        float zcenter=coord.position[i].z;

//        ROS_ERROR("x, y and z hand positions: %f %f %f", coord.position[i].x,coord.position[i].y,coord.position[i].z);
//        ROS_ERROR("size of coord.position: %lu", coord.position.size());

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

    //This will store the image ROI coordinates
    std_msgs::Int32MultiArray image_coord;
    image_coord.data.clear();

    //Total image dimensions (in pixels)
    int x_px_total=640;
    int y_px_total=480;

    //Total point cloud dimensions (in meters)
    pcl::PointXYZ total_max, total_min;
    pcl::getMinMax3D(cloud, total_min, total_max);

    //Total distance (x and y) in meters of the original point cloud
    float x_real_total=total_max.x-total_min.x;
    float y_real_total=total_max.y-total_min.y;

    //ROI point cloud dimensions (in meters)
    pcl::PointXYZ roi_max, roi_min;
    pcl::getMinMax3D(output_cloud, roi_min, roi_max);

    //      P1  _ P2
    //         | |
    //      P4 |_| P3

    //p1:
    image_coord.data.push_back(x_px_total/2-roi_min.x*x_px_total/x_real_total);
    image_coord.data.push_back(y_px_total/2-roi_max.y*y_px_total/y_real_total);

    //p3:
    image_coord.data.push_back(x_px_total/2-roi_max.x*x_px_total/x_real_total);
    image_coord.data.push_back(y_px_total/2-roi_min.y*y_px_total/y_real_total);


//    pcl::PointXYZ totmax, totmin, max, min;
//    pcl::getMinMax3D(cloud, totmin, totmax);
//    pcl::getMinMax3D(output_cloud, min, max);

//	  ROS_INFO("Image limits:\n x : %f %f \n y : %f %f\n", totmax.x, totmin.x, totmax.y, totmin.y);
//	  ROS_INFO("ROI limits:\n x : %f %f \n y : %f %f\n", max.x, min.x, max.y, min.y);
//    float distx, disty;
//    distx=abs(totmax.x-totmin.x);
//    disty=abs(totmax.y-totmin.y);

//    /*P1  _ P2
//         | |
//      P4 |_| P3	*/

//    int multx, multy;
//    float r=disty/distx;
//    if (distx>disty)
//    {
//        multx=640/distx;
//        multy=480/(r*disty);
//    }
//    else
//    {
//        multy=640/disty;
//        multx=480*r/distx;
//    }


//    float offx=0, offy=0;


//    offx=abs(totmin.x-min.x);
//    offy=abs(totmax.y-max.y);

//    //P1
//    image_coord.data.push_back((int)( multx*(abs(min.x)+ offx) ));	//x coordinates
//    image_coord.data.push_back((int)( multy*(abs(max.y)+ offy) ));	//y coordinates


//    offx=abs(totmax.x-max.x);
//    offy=abs(totmin.y-min.y);

//    //P3
//    image_coord.data.push_back((int)( multx*(abs(max.x)+ offx) ));	//x coordinates
//    image_coord.data.push_back((int)( multy*(abs(min.y)+ offy) ));	//y coordinates

    if (image_coord.data[0]>0 && image_coord.data[1]>0 && image_coord.data[2]>0 && image_coord.data[3]>0)
    {
        if(*coord.name.data()=="right_hand")
            coord_r_pub.publish (image_coord);
        else if (*coord.name.data()=="left_hand")
            coord_l_pub.publish (image_coord);

    }
}

void RoiSegmenter3D::coordinates (const TFG::HandLocConstPtr & msg)
{
    coord=*msg;
}
