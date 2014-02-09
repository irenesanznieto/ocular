#include "roisegmenter3D.h"

RoiSegmenter3D::RoiSegmenter3D()
{}

sensor_msgs::PointCloud2 RoiSegmenter3D::segment( const sensor_msgs::PointCloud2ConstPtr &cloud )
{
    sensor_msgs::PointCloud2 cloud_filtered;

    //make 3 passThrough filters, one for each coordinate
    pcl::PassThrough<sensor_msgs::PointCloud2> x, y, z;

    //set input cloud
    x.setInputCloud(cloud);
    y.setInputCloud(cloud);
    z.setInputCloud(cloud);

    //x and y should be the same -> the bounding box of an open or closed hand is approximately a square (not a rectangle)
    box_size.x=0.1;
    box_size.y=box_size.x;
    box_size.z=0.05;

    for (unsigned int i=0; i<coord.position.size(); i++)
    {
        //set limits  --> assuming the obtained position is the center, filter a cube
        x.setFilterFieldName("x");
        x.setFilterLimits(coord.position[i].x-box_size.x,coord.position[i].x+box_size.x); // unit : meter
        y.setFilterFieldName("y");
        y.setFilterLimits(coord.position[i].y-box_size.y,coord.position[i].y+box_size.y); // unit : meter
        z.setFilterFieldName("z");
        z.setFilterLimits(coord.position[i].z-box_size.z,coord.position[i].z+box_size.z); // unit : meter

        //filter
        x.filter(cloud_filtered);
        y.filter(cloud_filtered);
        z.filter(cloud_filtered);

    }

    //return ROI 3D
    return (cloud_filtered);
}


TFG::HandLocPx RoiSegmenter3D:: distance2px()
{
    TFG::HandLocPx image_coord;
    image_coord.points.data.clear();


    for (unsigned int i=0; i<coord.position.size(); i++)
    {
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

        //        hand_center_px.first= pin_hole_const.x-f * coord.position[i].x/coord.position[i].z;
        //        hand_center_px.second = pin_hole_const.y-f * coord.position[i].y/coord.position[i].z;



        pcl::PointXY p1, p2;
        p1.x=pin_hole_const.x-f * (coord.position[i].x-box_size.x)/coord.position[i].z;
        p1.y=pin_hole_const.y-f * (coord.position[i].y-box_size.y)/coord.position[i].z;


        p2.x=pin_hole_const.x-f * (coord.position[i].x+box_size.x)/coord.position[i].z;
        p2.y=pin_hole_const.y-f * (coord.position[i].y+box_size.y)/coord.position[i].z;


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

    return(image_coord);

}

void RoiSegmenter3D::coordinates (const TFG::HandLoc & msg)
{
    coord.header=msg.header;
    coord.user_id=msg.user_id;
    coord.name=msg.name;
    coord.position=msg.position;
}

void RoiSegmenter3D::setHandLoc (TFG::HandLoc &coord)
{
    this->coord=coord;
}
