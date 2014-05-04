#include "roisegmenter3D.h"

RoiSegmenter3D::RoiSegmenter3D()
{}


        pcl::PCLPointCloud2 RoiSegmenter3D::segment( const pcl::PCLPointCloud2ConstPtr &cloud )
{
//    if (!coord.position.empty() && !this->hand_name.empty())
//    {

        pcl::PCLPointCloud2 cloud_filtered;

        //make 3 passThrough filters, one for each coordinate
        pcl::PassThrough<pcl::PCLPointCloud2 > x, y, z;

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
            if (coord.name[i]==this->hand_name)
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
        }

        //return ROI 3D
        return (cloud_filtered);

//    }
}


ocular::HandLocPx RoiSegmenter3D:: distance2px()
{
    ocular::HandLocPx image_coord;
    image_coord.points.clear();


    for (unsigned int i=0; i<coord.position.size(); i++)
    {
        if (coord.name[i]==this->hand_name)
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
            image_coord.points.push_back(p1.x);
            image_coord.points.push_back(p1.y);

            //p3:
            image_coord.points.push_back(p2.x);
            image_coord.points.push_back(p2.y);


            //        std::cerr<<"SQUARE: P1: "<<image_coord.data[0]<<" "<<image_coord.data[1]<<std::endl<<image_coord.data[2]<<" "<<image_coord.data[3]<<std::endl;
            if (image_coord.points[0]>0 && image_coord.points[1]>0 && image_coord.points[2]>0 && image_coord.points[3]>0)
            {
                image_coord.name.push_back(coord.name[i]);
            }
        }

    }

    return(image_coord);

}

void RoiSegmenter3D::coordinates (const ocular::HandLoc & msg)
{
    coord.header=msg.header;
    coord.user_id=msg.user_id;
    coord.name=msg.name;
    coord.position=msg.position;
}

void RoiSegmenter3D::setHandLoc (ocular::HandLoc &coord)
{
    this->coord=coord;
}

ocular::HandLoc RoiSegmenter3D::getHandLoc ()
{
    return coord;
}

void RoiSegmenter3D:: setHandName(std::string hand_name)
{
    this->hand_name=hand_name;
}
