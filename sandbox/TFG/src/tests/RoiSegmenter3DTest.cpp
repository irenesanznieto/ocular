#include "../libraries/libraries/roisegmenter3D.h"
#include <gtest/gtest.h>


class RoiSegmenter3DTest : public testing::Test
{

public:
    RoiSegmenter3D roiseg3D;
    TFG::HandLoc msg_hand_loc;

    sensor_msgs::PointCloud2 msg_cloud;


    virtual void SetUp()
    {
        msg_hand_loc.header.seq=187;
        msg_hand_loc.header.stamp.sec=1390833331;
        msg_hand_loc.header.stamp.nsec=843339980;
        msg_hand_loc.header.frame_id="openni_depth_frame";
        msg_hand_loc.user_id=1;
        msg_hand_loc.name.push_back("left_hand");
//        msg_hand_loc.name.push_back("right_hand");

//        msg_hand_loc.position.resize(2);
        msg_hand_loc.position.resize(1);


        msg_hand_loc.position[0].x=0;
        msg_hand_loc.position[0].y=0;
        msg_hand_loc.position[0].z=0.7;

//        msg_hand_loc.position[1].x=0;
//        msg_hand_loc.position[1].y=0;
//        msg_hand_loc.position[1].z=0.7;






        // Fill the cloud data

//        //        Header
//        msg_cloud.header.seq=187;
//        msg_cloud.header.stamp.sec=1390833331;
//        msg_cloud.header.stamp.nsec=843339980;
//        msg_cloud.header.frame_id="openni_depth_frame";

  pcl::PointCloud<pcl::PointXYZ>::Ptr pcl_cloud (new pcl::PointCloud<pcl::PointXYZ>);
        pcl_cloud->width  = 3;
        pcl_cloud->height = 1;
        pcl_cloud->points.resize (pcl_cloud->width*pcl_cloud->height);


        pcl_cloud->points[0].x=0.01;
        pcl_cloud->points[0].y=0;
        pcl_cloud->points[0].z=0.7;

        pcl_cloud->points[1].x=0;
        pcl_cloud->points[1].y=0;
        pcl_cloud->points[1].z=0.7;

        pcl_cloud->points[2].x=0.03;
        pcl_cloud->points[2].y=0;
        pcl_cloud->points[2].z=0.7;

        pcl::toROSMsg(*pcl_cloud, msg_cloud);

   }

    virtual void TearDown()
    {
    }
};

TEST_F(RoiSegmenter3DTest,segment)
{
    sensor_msgs::PointCloud2 result_cloud;
    const sensor_msgs::PointCloud2ConstPtr& msg_cloud_ptr = boost::make_shared<sensor_msgs::PointCloud2>(msg_cloud);

    roiseg3D.setHandLoc(msg_hand_loc);
    result_cloud=roiseg3D.segment(msg_cloud_ptr);

    //TEST


    //There should pass all the points, and result in an unordered point cloud, hence:
    EXPECT_EQ (1, result_cloud.height);
    EXPECT_EQ (3, result_cloud.width);

}


TEST_F(RoiSegmenter3DTest,distance2px)
{
    TFG::HandLocPx result;
    result=roiseg3D.distance2px();

    //TEST
}

TEST_F(RoiSegmenter3DTest,coordinates)
{
    roiseg3D.coordinates(msg_hand_loc);
    TFG::HandLoc coordinates=roiseg3D.getHandLoc();

    //TEST
    EXPECT_EQ(0,coordinates.position[0].x);
    EXPECT_EQ(0,coordinates.position[0].y);
    EXPECT_EQ(0.7,coordinates.position[0].z);
}



int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
