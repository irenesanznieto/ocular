#include "../libraries/libraries/featureextractor3D.h"
#include <gtest/gtest.h>


class FeatureExtractor3DTest : public testing::Test
{

public:

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

//TEST_F(FeatureExtractor3DTest,segment)
//{

//    //    EXPECT_EQ (1, variable);
//}




int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
