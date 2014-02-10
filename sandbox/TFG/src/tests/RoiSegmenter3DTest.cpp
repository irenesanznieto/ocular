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
        msg_hand_loc.name.push_back("right_hand");

        msg_hand_loc.position.resize(2);

        msg_hand_loc.position[0].x=0;
        msg_hand_loc.position[0].y=0;
        msg_hand_loc.position[0].z=0.7;

        msg_hand_loc.position[1].x=0;
        msg_hand_loc.position[1].y=0;
        msg_hand_loc.position[1].z=0.7;






        // Fill in the cloud data --> failing here :S

        //        Header
        msg_cloud.header.seq=187;
        msg_cloud.header.stamp.sec=1390833331;
        msg_cloud.header.stamp.nsec=843339980;
        msg_cloud.header.frame_id="openni_depth_frame";

        msg_cloud.width  = 3;
        msg_cloud.height = 1;
        msg_cloud.data.resize (msg_cloud.width*msg_cloud.height);

        msg_cloud.data.push_back(-0.2);
        msg_cloud.data.push_back(0);
        msg_cloud.data.push_back(0);

        msg_cloud.data.push_back(0);
        msg_cloud.data.push_back(0);
        msg_cloud.data.push_back(0);

        msg_cloud.data.push_back(0.2);
        msg_cloud.data.push_back(0);
        msg_cloud.data.push_back(0);

    }

    virtual void TearDown()
    {
    }
};

TEST_F(RoiSegmenter3DTest,segment)
{
    sensor_msgs::PointCloud2 result;
    const sensor_msgs::PointCloud2ConstPtr& msg_cloud_ptr = boost::make_shared<sensor_msgs::PointCloud2>(msg_cloud);

    roiseg3D.setHandLoc(msg_hand_loc);
    result=roiseg3D.segment(msg_cloud_ptr);

    //TEST
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

    //TEST
//    EXPECT_EQ();

}


int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
