#include "../libraries/nodes/FeatureExtractor2DNode.h"

int main (int argc,char* argv[])
{
    ros::init(argc, argv, "FEATUREEXTRACTOR2D");
    FeatureExtractor2DNode featureExtractor2D;

    ros::spin();

    return 0;
}
