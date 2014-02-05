#include "../libraries/libraries/roisegmenter3D.h"
#include <gtest/gtest.h>


class RoiSegmenter3DTest : public testing::Test
{

public:
    RoiSegmenter3D roiseg3D;
//    TFG::HandLoc example;

    virtual void SetUp()
    {
        //    example.header=;
        //    example.user_id=;
        //    example.name=;
        //    example.position=;
    }

    virtual void TearDown()
    {
    }
};

TEST_F(RoiSegmenter3DTest,segment)
{

}


TEST_F(RoiSegmenter3DTest,distance2px)
{
//    roiseg3D.setHandLoc(example);
}

TEST_F(RoiSegmenter3DTest,coordinates)
{
//    roiseg3D.coordinates(example);
}


int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
