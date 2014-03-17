#include "../libraries/libraries/featureextractor2D.h"
#include <gtest/gtest.h>
#include <iostream>

class FeatureExtractor2DTest : public testing::Test
{

public:

    FeatureExtractor2D fe2d;
    TFG::HandImage msg;
    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {
    }
};

TEST_F(FeatureExtractor2DTest,extract_features)
{

    const TFG::HandImageConstPtr  msg_ptr=boost::make_shared<TFG::HandImage>(msg);
    fe2d.extract_features(msg_ptr);
}


int main (int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
