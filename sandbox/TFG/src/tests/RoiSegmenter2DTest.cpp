#include "../libraries/libraries/roisegmenter2D.h"
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>

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


        msg_hand_loc_px.points.push_back(50);
        msg_hand_loc_px.points.push_back(50);
        msg_hand_loc_px.points.push_back(200);
        msg_hand_loc_px.points.push_back(200);

        msg_hand_loc_px.points.push_back(0);
        msg_hand_loc_px.points.push_back(0);
        msg_hand_loc_px.points.push_back(3);
        msg_hand_loc_px.points.push_back(3);


//        msg_hand_loc_px.points.push_back(5);
//        msg_hand_loc_px.points.push_back(6);
//        msg_hand_loc_px.points.push_back(7);
//        msg_hand_loc_px.points.push_back(8);



//       // Fill the image data
        msg_image.height=4;
        msg_image.width=4;
        msg_image.encoding=sensor_msgs::image_encodings::BGR8;

        msg_image.step=1;
        msg_image.is_bigendian=0;

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
    const TFG::HandLocPxConstPtr& msg_hand_loc_px_ptr = boost::make_shared<TFG::HandLocPx>(msg_hand_loc_px);
    roiseg2D.coordinates(msg_hand_loc_px_ptr);


//    std::string sys_command="find . -print | grep 'sandbox/TFG/data/test/' > dummy.txt";
//    system(sys_command.c_str());

//    std::string path;
//    std::ifstream myfile;
//    myfile.open ("dummy.txt");
//    myfile >>path;

//    myfile.close();

//    std::cout <<path<<std::endl;

//    system("rm dummy.txt");

//    TFG::HandImage result_image=roiseg2D.segment(roiseg2D.setInputImage(path));

    TFG::HandImage result_image=roiseg2D.segment(roiseg2D.setInputImage("/home/peko/tfg_git/sandbox/TFG/data/test/ros_groovy.jpg"));
    //TEST
    EXPECT_EQ (2, result_image.name.size());
    EXPECT_EQ(2, result_image.image.size());
    EXPECT_EQ(150, result_image.image[0].width);
    EXPECT_EQ(150, result_image.image[0].height);
}


TEST_F(RoiSegmenter2DTest,checkLimits)
{
    //if x> 640 --> x=640; if x<0 --> x=0
    //if y> 480 --> y=480; if y<0 --> y=0

    int x=660;
    int y=500;

    bool out=roiseg2D.checkLimits(x,y);

    EXPECT_EQ(true, out);
    EXPECT_EQ(true, out);


    x=-20;
    y=-100;

   out= roiseg2D.checkLimits(x,y);

    EXPECT_EQ(true,out);
    EXPECT_EQ(true, out);


    x=20;
    y=100;

    out=roiseg2D.checkLimits(x,y);

    EXPECT_EQ(false, out);
    EXPECT_EQ(false, out);
}

TEST_F(RoiSegmenter2DTest,coordinates)
{
    const TFG::HandLocPxConstPtr& msg_hand_loc_px_ptr = boost::make_shared<TFG::HandLocPx>(msg_hand_loc_px);
    roiseg2D.coordinates(msg_hand_loc_px_ptr);

    TFG::HandLocPx coordinates=roiseg2D.getHandLocPx();


    //TEST
    EXPECT_EQ(50,coordinates.points[0]);
    EXPECT_EQ(50,coordinates.points[1]);
    EXPECT_EQ(200,coordinates.points[2]);
    EXPECT_EQ(200,coordinates.points[3]);

    EXPECT_EQ(0,coordinates.points[4]);
    EXPECT_EQ(0,coordinates.points[5]);
    EXPECT_EQ(3,coordinates.points[6]);
    EXPECT_EQ(3,coordinates.points[7]);
}



int main (int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
