#include "../libraries/libraries/roisegmenter2D.h"
#include <gtest/gtest.h>


class RoiSegmenter2DTest : public testing::Test
{

public:
    RoiSegmenter2D roiseg2D;
    TFG::HandLocPx msg_hand_loc_px;
    sensor_msgs::Image msg_image;

    virtual void SetUp()
    {
        msg_hand_loc_px.header.seq=187;
        msg_hand_loc_px.header.stamp.sec=1390833331;
        msg_hand_loc_px.header.stamp.nsec=843339980;
        msg_hand_loc_px.header.frame_id="openni_depth_frame";
        msg_hand_loc_px.user_id=1;
        msg_hand_loc_px.name.push_back("left_hand");
        msg_hand_loc_px.name.push_back("right_hand");


        msg_hand_loc_px.points.push_back(1);
        msg_hand_loc_px.points.push_back(2);
        msg_hand_loc_px.points.push_back(3);
        msg_hand_loc_px.points.push_back(4);

        msg_hand_loc_px.points.push_back(5);
        msg_hand_loc_px.points.push_back(6);
        msg_hand_loc_px.points.push_back(7);
        msg_hand_loc_px.points.push_back(8);



       // Fill the image data
        msg_image.height=4;
        msg_image.width=4;
        msg_image.encoding="bgr8";

        //This will "paint" one line in white and another in black, 4 lines in total
        msg_image.data.push_back(255);
        msg_image.data.push_back(255);
        msg_image.data.push_back(255);
        msg_image.data.push_back(255);

        msg_image.data.push_back(0);
        msg_image.data.push_back(0);
        msg_image.data.push_back(0);
        msg_image.data.push_back(0);

        msg_image.data.push_back(255);
        msg_image.data.push_back(255);
        msg_image.data.push_back(255);
        msg_image.data.push_back(255);

        msg_image.data.push_back(0);
        msg_image.data.push_back(0);
        msg_image.data.push_back(0);
        msg_image.data.push_back(0);



   }

    virtual void TearDown()
    {
    }
};

TEST_F(RoiSegmenter2DTest,segment)
{
//    TFG::HandImage result_image;
//    const sensor_msgs::ImageConstPtr& msg_image_ptr = boost::make_shared<sensor_msgs::Image>(msg_image);

//    const TFG::HandLocPxConstPtr& msg_hand_loc_px_ptr = boost::make_shared<TFG::HandLocPx>(msg_hand_loc_px);
//    roiseg2D.coordinates(msg_hand_loc_px_ptr);


//    result_image=roiseg2D.segment(msg_image_ptr);


    //TEST

//    EXPECT_EQ (2, result_image.name.size());


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
    EXPECT_EQ(1,coordinates.points[0]);
    EXPECT_EQ(2,coordinates.points[1]);
    EXPECT_EQ(3,coordinates.points[2]);
    EXPECT_EQ(4,coordinates.points[3]);

    EXPECT_EQ(5,coordinates.points[4]);
    EXPECT_EQ(6,coordinates.points[5]);
    EXPECT_EQ(7,coordinates.points[6]);
    EXPECT_EQ(8,coordinates.points[7]);
}



int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
