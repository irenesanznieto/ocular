
#include "../libraries/libraries/roisegmenter2D.h"
#include <gtest/gtest.h>


class RoiSegmenter2DTest : public testing::Test
{

public:
    RoiSegmenter2D roiseg2D;
    TFG::HandLocPx msg_hand_loc_px;

    virtual void SetUp()
    {
        msg_hand_loc_px.header.seq=187;
        msg_hand_loc_px.header.stamp.sec=1390833331;
        msg_hand_loc_px.header.stamp.nsec=843339980;
        msg_hand_loc_px.header.frame_id="openni_depth_frame";
        msg_hand_loc_px.user_id=1;
        msg_hand_loc_px.name.push_back("left_hand");
        msg_hand_loc_px.name.push_back("right_hand");


        msg_hand_loc_px.points.push_back(100);
        msg_hand_loc_px.points.push_back(200);
        msg_hand_loc_px.points.push_back(300);
        msg_hand_loc_px.points.push_back(400);

        msg_hand_loc_px.points.push_back(100);
        msg_hand_loc_px.points.push_back(200);
        msg_hand_loc_px.points.push_back(300);
        msg_hand_loc_px.points.push_back(400);



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
    const TFG::HandLocPxConstPtr& msg_hand_loc_px_ptr = boost::make_shared<TFG::HandLocPx>(msg_hand_loc_px);
    roiseg2D.coordinates(msg_hand_loc_px_ptr);

    TFG::HandLocPx coordinates=roiseg2D.getHandLocPx();


    //TEST
    EXPECT_EQ(100,coordinates.points[0]);
    EXPECT_EQ(200,coordinates.points[1]);
    EXPECT_EQ(300,coordinates.points[2]);
    EXPECT_EQ(400,coordinates.points[3]);

    EXPECT_EQ(100,coordinates.points[4]);
    EXPECT_EQ(200,coordinates.points[5]);
    EXPECT_EQ(300,coordinates.points[6]);
    EXPECT_EQ(400,coordinates.points[7]);
}



int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
