#include "../libraries/libraries/dataparser.h"
#include <gtest/gtest.h>


class DataParserTest : public testing::Test
{

public:

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

//TEST_F(DataParserTest,segment)
//{

//    //    EXPECT_EQ (1, variable);
//}




int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

