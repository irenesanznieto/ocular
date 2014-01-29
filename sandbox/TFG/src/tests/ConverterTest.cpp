#include "../libraries/converter.h"
#include <gtest/gtest.h>
#include <pi_tracker/Skeleton.h>


// Declare the tests

TEST(Converter,input_callback)
{
//    Converter c;
    pi_tracker::SkeletonConstPtr message;

//    message->header.seq=187;
//    message->header.stamp.sec=1390833331;
//    message->header.stamp.nsec=843339980;
//    message.header.frame_id.push_back("openni_depth_frame");

    message->user_id=1;
//            input_callback(message.ConstPtr);

//    message->name=['head', 'neck', 'torso', 'left_shoulder', 'left_elbow', 'left_hand', 'right_shoulder', 'right_elbow', 'right_hand', 'left_hip', 'left_knee', 'left_foot', 'right_hip', 'right_knee', 'right_foot'];
//        message->confidence=[0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0];

//        message->position[0].x=-0.123597961426;
//        message->position[0].y=0.716625366211;
//        message->position[0].z=0.714454772949;

//    input_callback(message);

    EXPECT_EQ(1, message->user_id);

}



// Run all the tests declared with TEST()
int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
