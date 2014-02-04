#include "../libraries/libraries/converter.h"

#include <gtest/gtest.h>
#include <pi_tracker/Skeleton.h>

/*!
* \brief Test that checks the correct behaviour of the handCoordinatesExtractor method from the Converter class,
*the method that extracts the hands information from the pi_tracker::Skeleton message
*/

TEST(Converter,handCoordinatesExtractor)
{
    
    Converter c;
    pi_tracker::Skeleton message;

//        Header
    message.header.seq=187;
    message.header.stamp.sec=1390833331;
    message.header.stamp.nsec=843339980;
    message.header.frame_id="openni_depth_frame";

//        User ID
    message.user_id=1;

//        Name
    message.name.push_back("head");
    message.name.push_back("neck");
    message.name.push_back("torso");
    message.name.push_back("left_shoulder");
    message.name.push_back("left_elbow");
    message.name.push_back("left_hand");
    message.name.push_back("right_shoulder");
    message.name.push_back("right_elbow");
    message.name.push_back( "right_hand");
    message.name.push_back("left_hip");
    message.name.push_back("left_knee");
    message.name.push_back("left_foot");
    message.name.push_back("right_hip");
    message.name.push_back("right_knee");
    message.name.push_back("right_foot");

//        Confidence
    for (int i=0; i<14; i++)
        message.confidence.push_back(0.0);

//        Position
    message.position.resize(15);

    message.position[0].x=-0.123597961426;
    message.position[0].y=0.716625366211;
    message.position[0].z=0.714454772949;

    message.position[1].x=-0.146407974243;
    message.position[1].y=0.478561706543;
    message.position[1].z=0.765637329102;


    message.position[2].x=-0.147514678955;
    message.position[2].y=0.309718017578;
    message.position[2].z=0.799335021973;


    message.position[3].x= -0.290514434814;
    message.position[3].y= 0.471770446777;
    message.position[3].z= 0.726876525879;

    message.position[4].x= -0.332415435791;
    message.position[4].y= 0.247058441162;
    message.position[4].z= 0.784785827637;

    message.position[5].x= -0.382902069092;
    message.position[5].y= -0.0380207214355;
    message.position[5].z= 0.759758544922;

    message.position[6].x= -0.00230148077011;
    message.position[6].y= 0.485353027344;
    message.position[6].z= 0.804398132324;

    message.position[7].x= 0.0418956336975;
    message.position[7].y= 0.264750793457;
    message.position[7].z= 0.878666870117;

    message.position[8].x= -0.183200836182;
    message.position[8].y= -0.169277770996;
    message.position[8].z= 0.592351806641;

    message.position[9].x= -0.228035507202;
    message.position[9].y= 0.137131759644;
    message.position[9].z= 0.811672424316;

    message.position[10].x= -0.19866317749;
    message.position[10].y= -0.254349899292;
    message.position[10].z= 0.883813720703;

    message.position[11].x= -0.184728942871;
    message.position[11].y= -0.552051208496;
    message.position[11].z= 0.938119689941;


    message.position[12].x= -0.0692072601318;
    message.position[12].y= 0.144616867065;
    message.position[12].z= 0.854393005371;

    message.position[13].x= -0.0496014556885;
    message.position[13].y= -0.227107955933;
    message.position[13].z= 0.864401611328;

    message.position[14].x= -0.0600204048157;
    message.position[14].y= -0.517969543457;
    message.position[14].z= 0.936475585938;

//        Orientation -> not used and hence, not tested
    TFG::HandLoc result=c.handCoordinatesExtractor(message);


//        Header
    EXPECT_EQ(187, result.header.seq);
    EXPECT_EQ(1390833331, result.header.stamp.sec);
    EXPECT_EQ(843339980, result.header.stamp.nsec);
    EXPECT_EQ("openni_depth_frame", result.header.frame_id);

//        User ID
    EXPECT_EQ(1, result.user_id);

//        Name
    EXPECT_EQ("left_hand", result.name[0]);
    EXPECT_EQ("right_hand", result.name[1]);


//        Position
    EXPECT_EQ( -0.382902069092, result.position[0].x);
    EXPECT_EQ( -0.0380207214355, result.position[0].y);
    EXPECT_EQ( 0.759758544922, result.position[0].z);

    EXPECT_EQ( -0.183200836182, result.position[1].x);
    EXPECT_EQ( -0.169277770996, result.position[1].y);
    EXPECT_EQ( 0.592351806641, result.position[1].z);

}



int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
