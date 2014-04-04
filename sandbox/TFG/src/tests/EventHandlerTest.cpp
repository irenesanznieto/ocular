#include "../libraries/libraries/eventhandler.h"
#include <gtest/gtest.h>


class EventHandlerTest : public testing::Test
{

public:

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(EventHandlerTest,segment)
{

    //    EXPECT_EQ (1, variable);
}




int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

