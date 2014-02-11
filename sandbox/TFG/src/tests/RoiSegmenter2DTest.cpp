
#include "../libraries/libraries/roisegmenter2D.h"
#include <gtest/gtest.h>


class RoiSegmenter2DTest : public testing::Test
{

public:
    RoiSegmenter2D roiseg2D;
//    TFG::HandLocPx msg_hand_loc;



    virtual void SetUp()
    {
//        msg_hand_loc.header.seq=187;
//        msg_hand_loc.header.stamp.sec=1390833331;
//        msg_hand_loc.header.stamp.nsec=843339980;
//        msg_hand_loc.header.frame_id="openni_depth_frame";
//        msg_hand_loc.user_id=1;
//        msg_hand_loc.name.push_back("left_hand");
//        msg_hand_loc.name.push_back("right_hand");

//        msg_hand_loc.position.resize(2);

//        msg_hand_loc.position[0].x=0;
//        msg_hand_loc.position[0].y=0;
//        msg_hand_loc.position[0].z=0.7;

//        msg_hand_loc.position[1].x=0;
//        msg_hand_loc.position[1].y=0;
//        msg_hand_loc.position[1].z=0.7;


       // Fill the image data



   }

    virtual void TearDown()
    {
    }
};

TEST_F(RoiSegmenter2DTest,segment)
{
//    sensor_msgs::PointCloud2 result_cloud;
//    const sensor_msgs::PointCloud2ConstPtr& msg_cloud_ptr = boost::make_shared<sensor_msgs::PointCloud2>(msg_cloud);

//    roiseg2D.setHandLoc(msg_hand_loc);
//    result_cloud=roiseg2D.segment(msg_cloud_ptr);

//    //TEST

//    pcl::PointCloud<pcl::PointXYZ> result_pcl_cloud;
//    pcl::fromROSMsg(result_cloud, result_pcl_cloud);

//    //There should pass all the points, and result in an unordered point cloud, hence:
//    EXPECT_EQ (1, result_cloud.height);
//    EXPECT_EQ (3, result_cloud.width);

//    EXPECT_EQ ((float)0.01,result_pcl_cloud.points[0].x);
//    EXPECT_EQ ((float)0,result_pcl_cloud.points[0].y);
//    EXPECT_EQ ((float)0.7,result_pcl_cloud.points[0].z);

//    EXPECT_EQ ((float)0,result_pcl_cloud.points[1].x);
//    EXPECT_EQ ((float)0,result_pcl_cloud.points[1].y);
//    EXPECT_EQ ((float)0.7,result_pcl_cloud.points[1].z);

//    EXPECT_EQ ((float)0.03,result_pcl_cloud.points[2].x);
//    EXPECT_EQ ((float)0,result_pcl_cloud.points[2].y);
//    EXPECT_EQ ((float)0.7,result_pcl_cloud.points[2].z);

}


TEST_F(RoiSegmenter2DTest,checkLimits)
{
    //if x> 640 --> x=640; if x<0 --> x=0
    //if y> 480 --> y=480; if y<0 --> y=0

    int x=660;
    int y=500;

    roiseg2D.checkLimits(x,y);

    EXPECT_EQ(640, x);
    EXPECT_EQ(480, y);


    x=-20;
    y=-100;

    roiseg2D.checkLimits(x,y);

    EXPECT_EQ(0, x);
    EXPECT_EQ(0, y);


    x=20;
    y=100;

    roiseg2D.checkLimits(x,y);

    EXPECT_EQ(20, x);
    EXPECT_EQ(100, y);



}

TEST_F(RoiSegmenter2DTest,coordinates)
{
//    roiseg2D.coordinates(msg_hand_loc);
//    TFG::HandLoc coordinates=roiseg2D.getHandLoc();

//    //TEST
//    EXPECT_EQ(0,coordinates.position[0].x);
//    EXPECT_EQ(0,coordinates.position[0].y);
//    EXPECT_EQ(0.7,coordinates.position[0].z);
}



int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
