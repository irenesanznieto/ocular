#include "../libraries/libraries/featureextractor2D.h"
#include <gtest/gtest.h>
#include <iostream>

class FeatureExtractor2DTest : public testing::Test
{

public:

    FeatureExtractor2D fe2d;
    ocular::HandImage msg;
    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {
    }
};

TEST_F(FeatureExtractor2DTest,extract_features)
{
    const ocular::HandImageConstPtr  msg_ptr=boost::make_shared<ocular::HandImage>(msg);
    ocular::HandImage result=fe2d.extract_features(msg_ptr);

    EXPECT_FALSE(msg_ptr->image.size(),result.image.size());
//    EXPECT_TRUE()

}


int main (int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
