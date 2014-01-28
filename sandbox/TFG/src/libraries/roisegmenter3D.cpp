#include "roisegmenter3D.h"

RoiSegmenter3D::RoiSegmenter3D()
{
    point_cloud_sub= nh.subscribe <sensor_msgs::PointCloud2> ("input", 1, &RoiSegmenter3D::segment, this);
    point_cloud_pub=nh.advertise <sensor_msgs::PointCloud2> ("output_cloud", 1);

    //    coord_r_pub= nh.advertise <std_msgs::Int32MultiArray> ("output_r_coord", 1);
    //    coord_l_pub= nh.advertise <std_msgs::Int32MultiArray> ("output_l_coord", 1);

    coord_pub= nh.advertise <TFG::HandLocPx> ("output_coord", 1);

    coord_sub=nh.subscribe<TFG::HandLoc> ("input_coord", 1, &RoiSegmenter3D::coordinates, this);




}

void RoiSegmenter3D:: segment (const sensor_msgs::PointCloud2ConstPtr & cloud )
{
    sensor_msgs::PointCloud2 cloud_filtered;

    //make 3 passThrough filters, one for each coordinate
    pcl::PassThrough<sensor_msgs::PointCloud2> x, y, z;

    //set input cloud
    x.setInputCloud(cloud);
    y.setInputCloud(cloud);
    z.setInputCloud(cloud);


    //TODO: put this as a function of the distance to the kinect --> is it necessary?
    pcl::PointXYZ box_size;
    //x and y should be the same -> the bounding box of an open or closed hand is approximately a square (not a rectangle)
    box_size.x=0.1;
    box_size.y=box_size.x;
    box_size.z=0.05;

    TFG::HandLocPx image_coord;


    for (unsigned int i=0; i<coord.position.size(); i++)
    {

        pcl::PointXYZ hand_center;
        hand_center.x= coord.position[i].x;
        hand_center.y=coord.position[i].y;
        hand_center.z=coord.position[i].z;

        //set limits  --> assuming the obtained position is the center, filter a cube
        x.setFilterFieldName("x");
        x.setFilterLimits(hand_center.x-box_size.x,hand_center.x+box_size.x); // unit : meter
        y.setFilterFieldName("y");
        y.setFilterLimits(hand_center.y-box_size.y,hand_center.y+box_size.y); // unit : meter
        z.setFilterFieldName("z");
        z.setFilterLimits(hand_center.z-box_size.z,hand_center.z+box_size.z); // unit : meter

        //filter
        x.filter(cloud_filtered);
        y.filter(cloud_filtered);
        z.filter(cloud_filtered);

        //        3D Pin hole model for the camera

        //Initial computation used for the pin-hole model

        int half_width=320;
        int half_height=240;

        //constant=120 && f=500--> acceptable resolution
        float constant=0;

        //This variable will store the constant values used for the pin-hole camera model, which will be computed at startup
        pcl::PointXY pin_hole_const;

        pin_hole_const.x = half_width + constant;
        pin_hole_const.y = half_height + constant;

        float f=520;

        //        hand_center_px.first= pin_hole_const.x-f * hand_center.x/hand_center.z;
        //        hand_center_px.second = pin_hole_const.y-f * hand_center.y/hand_center.z;

        image_coord.points.data.clear();


        pcl::PointXY p1, p2;
        p1.x=pin_hole_const.x-f * (hand_center.x-box_size.x)/hand_center.z;
        p1.y=pin_hole_const.y-f * (hand_center.y-box_size.y)/hand_center.z;


        p2.x=pin_hole_const.x-f * (hand_center.x+box_size.x)/hand_center.z;
        p2.y=pin_hole_const.y-f * (hand_center.y+box_size.y)/hand_center.z;


        //p1:coord.name[i]
        image_coord.points.data.push_back(p1.x);
        image_coord.points.data.push_back(p1.y);

        //p3:
        image_coord.points.data.push_back(p2.x);
        image_coord.points.data.push_back(p2.y);


        //        std::cerr<<"SQUARE: P1: "<<image_coord.data[0]<<" "<<image_coord.data[1]<<std::endl<<image_coord.data[2]<<" "<<image_coord.data[3]<<std::endl;
        if (image_coord.points.data[0]>0 && image_coord.points.data[1]>0 && image_coord.points.data[2]>0 && image_coord.points.data[3]>0)
        {
            image_coord.name.push_back(coord.name[i].data());
        }

    }
    coord_pub.publish (image_coord);

    //publish ROI 3D
    point_cloud_pub.publish(cloud_filtered);

}


void RoiSegmenter3D:: distance2px(pcl::PointCloud<pcl::PointXYZ>& cloud, pcl::PointCloud <pcl::PointXYZ>& output_cloud)
{

}

void RoiSegmenter3D::coordinates (const TFG::HandLocConstPtr & msg)
{
    //    std::cerr<<"Message from pi_tracker: "<<*msg.get()<<std::endl;
    //    coord=*msg;
    coord.header=msg->header;
    coord.user_id=msg->user_id;
    coord.name=msg->name;
    coord.position=msg->position;

}
