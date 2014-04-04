#include "../libraries/libraries/algorithm2D.h"
#include <gtest/gtest.h>


class Algorithm2DTest : public testing::Test
{

public:

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

//TEST_F(Algorithm2DTest,segment)
//{

//    //    EXPECT_EQ (1, variable);
//}




int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


