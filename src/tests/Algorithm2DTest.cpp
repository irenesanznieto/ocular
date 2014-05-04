#include "../libraries/libraries/algorithm2D.h"
#include <gtest/gtest.h>


class Algorithm2DTest : public testing::Test
{

public:

    Algorithm2D alg2D;
    ocular::HandImage msg;


    virtual void SetUp()
    {

        // Fill the image data
        msg.image.resize(1);
        msg.image[0].height=4;
        msg.image[0].width=4;
        msg.image[0].encoding=sensor_msgs::image_encodings::MONO8;

        msg.image[0].step=1;
        msg.image[0].is_bigendian=0;

        //This will "paint" one line in white and another in black, 4 lines in total
        msg.image[0].data.push_back(255);
        msg.image[0].data.push_back(255);
        msg.image[0].data.push_back(255);
        msg.image[0].data.push_back(255);

        msg.image[0].data.push_back(0);
        msg.image[0].data.push_back(0);
        msg.image[0].data.push_back(0);
        msg.image[0].data.push_back(0);

        msg.image[0].data.push_back(255);
        msg.image[0].data.push_back(255);
        msg.image[0].data.push_back(255);
        msg.image[0].data.push_back(255);

        msg.image[0].data.push_back(0);
        msg.image[0].data.push_back(0);
        msg.image[0].data.push_back(0);
        msg.image[0].data.push_back(0);
    }

    virtual void TearDown()
    {
    }
};

//TEST_F(Algorithm2DTest, match2D)
//{
////    int Algorithm2D :: match2D(const ocular::HandImageConstPtr & msg)

//}

//TEST_F(Algorithm2DTest,add_descriptors)
//{

//}

//TEST_F(Algorithm2DTest,flann_comparison)
//{
//    //int Algorithm2D:: flann_comparison (cv::Mat  desc1,float threshold)

//}


int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


