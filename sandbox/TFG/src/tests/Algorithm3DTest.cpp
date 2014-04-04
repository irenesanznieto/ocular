#include "../libraries/libraries/dataparser.h"
#include <gtest/gtest.h>


class Algorithm3DTest : public testing::Test
{

public:

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(Algorithm3DTest,segment)
{

    //    EXPECT_EQ (1, variable);
}




int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


