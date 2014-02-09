#include "../libraries/libraries/roisegmenter3D.h"
#include <gtest/gtest.h>


class RoiSegmenter3DTest : public testing::Test
{

public:
    RoiSegmenter3D roiseg3D;
    TFG::HandLoc example;

    TFG::HandLoc result;

    virtual void SetUp()
    {
        example.header.seq=187;
        example.header.stamp.sec=1390833331;
        example.header.stamp.nsec=843339980;
        example.header.frame_id="openni_depth_frame";
        example.user_id=1;
        example.name.push_back("left_hand");
        example.name.push_back("right_hand");

        example.position.resize(2);

        example.position[0].x=-0.123597961426;
        example.position[0].y=0.716625366211;
        example.position[0].z=0.714454772949;

        example.position[1].x=-0.146407974243;
        example.position[1].y=0.478561706543;
        example.position[1].z=0.765637329102;

    }

    virtual void TearDown()
    {
    }
};

TEST_F(RoiSegmenter3DTest,segment)
{

    sensor_msgs::PointCloud2 msg, result;
//    result=roiseg3D.segment(msg);

}


TEST_F(RoiSegmenter3DTest,distance2px)
{
    //    result=roiseg3D.distance2px();
}

TEST_F(RoiSegmenter3DTest,coordinates)
{
    roiseg3D.coordinates(example);
}


int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
