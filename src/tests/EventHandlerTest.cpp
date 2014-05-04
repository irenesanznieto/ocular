#include "../libraries/libraries/eventhandler.h"
#include <gtest/gtest.h>
#include <iostream>


class EventHandlerTest : public testing::Test
{

public:

    EventHandler events;
    pi_tracker::Skeleton msg;


    virtual void SetUp()
    {
        //        Header
        msg.header.seq=187;
        msg.header.stamp.sec=1390833331;
        msg.header.stamp.nsec=843339980;
        msg.header.frame_id="openni_depth_frame";

        //        User ID
        msg.user_id=1;

        //        Name
        msg.name.push_back("head");
        msg.name.push_back("neck");
        msg.name.push_back("torso");
        msg.name.push_back("left_shoulder");
        msg.name.push_back("left_elbow");
        msg.name.push_back("left_hand");
        msg.name.push_back("right_shoulder");
        msg.name.push_back("right_elbow");
        msg.name.push_back( "right_hand");
        msg.name.push_back("left_hip");
        msg.name.push_back("left_knee");
        msg.name.push_back("left_foot");
        msg.name.push_back("right_hip");
        msg.name.push_back("right_knee");
        msg.name.push_back("right_foot");

        //        Confidence
        for (int i=0; i<14; i++)
            msg.confidence.push_back(0.0);

        //        Position
        msg.position.resize(15);

        msg.position[0].x=-0.123597961426;
        msg.position[0].y=0.716625366211;
        msg.position[0].z=0.714454772949;

        msg.position[1].x=-0.146407974243;
        msg.position[1].y=0.478561706543;
        msg.position[1].z=0.765637329102;


        msg.position[2].x=-0.147514678955;
        msg.position[2].y=0.309718017578;
        msg.position[2].z=0.799335021973;


        msg.position[3].x= -0.290514434814;
        msg.position[3].y= 0.471770446777;
        msg.position[3].z= 0.726876525879;

        msg.position[4].x= -0.332415435791;
        msg.position[4].y= 0.247058441162;
        msg.position[4].z= 0.784785827637;

        msg.position[5].x= -0.382902069092;
        msg.position[5].y= -0.0380207214355;
        msg.position[5].z= 0.759758544922;

        msg.position[6].x= -0.00230148077011;
        msg.position[6].y= 0.485353027344;
        msg.position[6].z= 0.804398132324;

        msg.position[7].x= 0.0418956336975;
        msg.position[7].y= 0.264750793457;
        msg.position[7].z= 0.878666870117;

        msg.position[8].x= -0.183200836182;
        msg.position[8].y= -0.169277770996;
        msg.position[8].z= 0.592351806641;

        msg.position[9].x= -0.228035507202;
        msg.position[9].y= 0.137131759644;
        msg.position[9].z= 0.811672424316;

        msg.position[10].x= -0.19866317749;
        msg.position[10].y= -0.254349899292;
        msg.position[10].z= 0.883813720703;

        msg.position[11].x= -0.184728942871;
        msg.position[11].y= -0.552051208496;
        msg.position[11].z= 0.938119689941;


        msg.position[12].x= -0.0692072601318;
        msg.position[12].y= 0.144616867065;
        msg.position[12].z= 0.854393005371;

        msg.position[13].x= -0.0496014556885;
        msg.position[13].y= -0.227107955933;
        msg.position[13].z= 0.864401611328;

        msg.position[14].x= -0.0600204048157;
        msg.position[14].y= -0.517969543457;
        msg.position[14].z= 0.936475585938;

        //        Orientation -> not used and hence, not tested
    }

    virtual void TearDown()
    {
    }
};

TEST_F(EventHandlerTest , select_event_hand)
{
    ocular::EventHandler result;
    result=events.select_event_hand(msg);

    EXPECT_EQ ("recognize", result.event);
    EXPECT_EQ ("recognize", result.last_event);

}





int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

