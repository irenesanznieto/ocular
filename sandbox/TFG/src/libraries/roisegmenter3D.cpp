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

//        pcl::PointXYZ hand_center_m;
//        hand_center_m.x=xcenter;
//        hand_center_m.y=ycenter;
//        hand_center_m.z=zcenter;
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

        std::pair <int, int> hand_center_px;
        std::cerr<<"pi_tracker's hand center: "<<xcenter<<" "<<ycenter<<std::endl;


        //esto sigue el modelo pin hole. la imagen est´a flipped, pero los dos puntitos corresponden a las manos
        //hay que cambiar el cx y cy y f;
        //falta un - por algun lado --> cuando se mueven las manos arriba los puntitos bajan

        int width=640;
        int height=480;

//        float constant=0.5; //default
        float constant=100;
        float cx = width/2 + constant;
        float cy = height/2 + constant;


        float f=566;
        float x=xcenter;
        float y=ycenter;
        float z=zcenter;
        hand_center_px.first= cx-f * x/z;
        hand_center_px.second = cy-f * y/z;


        std::cerr<<"hand center: "<<hand_center_px.first<<" "<<hand_center_px.second<<std::endl;
        std_msgs::Int32MultiArray image_coord;
        image_coord.data.clear();



        int size=50;

        //p1:
        image_coord.data.push_back(hand_center_px.first-size);
        image_coord.data.push_back(hand_center_px.second-size);

        //p3:
        image_coord.data.push_back(hand_center_px.first+size);
        image_coord.data.push_back(hand_center_px.second+size);

        std::cerr<<"SQUARE: P1: "<<image_coord.data[0]<<" "<<image_coord.data[1]<<std::endl<<image_coord.data[2]<<" "<<image_coord.data[3]<<std::endl;
        if (image_coord.data[0]>0 && image_coord.data[1]>0 && image_coord.data[2]>0 && image_coord.data[3]>0)
        {
            if(*coord.name.data()=="right_hand")
                coord_r_pub.publish (image_coord);
            else if (*coord.name.data()=="left_hand")
                coord_l_pub.publish (image_coord);

        }

        //        RoiSegmenter3D::distance2px(input_cloud, output_cloud);
    }

    //publish ROI 3D
    point_cloud_pub.publish(cloud_filtered);

}


void RoiSegmenter3D:: distance2px(pcl::PointCloud<pcl::PointXYZ>& cloud, pcl::PointCloud <pcl::PointXYZ>& output_cloud)
{

}


//void RoiSegmenter3D:: distance2px(pcl::PointCloud<pcl::PointXYZ>& cloud, pcl::PointCloud <pcl::PointXYZ>& output_cloud)
//{
//    //This will store the image ROI coordinates
//    std_msgs::Int32MultiArray image_coord;
//    image_coord.data.clear();

//    //Total image dimensions (in pixels)
//    int x_px_total=640;
//    int y_px_total=480;

//    //Total point cloud dimensions (in meters)
//    pcl::PointXYZ total_max, total_min;
//    pcl::getMinMax3D(cloud, total_min, total_max);

//    //Total distance (x and y) in meters of the original point cloud
//    float x_real_total=total_max.x-total_min.x;
//    float y_real_total=total_max.y-total_min.y;

//    //ROI point cloud dimensions (in meters)
//    pcl::PointXYZ roi_max, roi_min;
//    pcl::getMinMax3D(output_cloud, roi_min, roi_max);

//    //      P1  _ P2
//    //         | |
//    //      P4 |_| P3

//    //p1:
//    image_coord.data.push_back(x_px_total/2-roi_min.x*x_px_total/x_real_total);
//    image_coord.data.push_back(y_px_total/2-roi_max.y*y_px_total/y_real_total);

//    //p3:
//    image_coord.data.push_back(x_px_total/2-roi_max.x*x_px_total/x_real_total);
//    image_coord.data.push_back(y_px_total/2-roi_min.y*y_px_total/y_real_total);


//    if (image_coord.data[0]>0 && image_coord.data[1]>0 && image_coord.data[2]>0 && image_coord.data[3]>0)
//    {
//        if(*coord.name.data()=="right_hand")
//            coord_r_pub.publish (image_coord);
//        else if (*coord.name.data()=="left_hand")
//            coord_l_pub.publish (image_coord);

//    }
//}

void RoiSegmenter3D::coordinates (const TFG::HandLocConstPtr & msg)
{
//    std::cerr<<"Message from pi_tracker: "<<*msg.get()<<std::endl;
//    coord=*msg;
    coord.header=msg->header;
    coord.user_id=msg->user_id;
    coord.name=msg->name;
    coord.position=msg->position;

}
