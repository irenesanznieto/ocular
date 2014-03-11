#include "../libraries/nodes/FeatureExtractor3DNode.h"

int main (int argc,char* argv[])
{
    ros::init(argc, argv, "FEATUREEXTRACTOR3D");
    FeatureExtractor3DNode featureExtractor3D;

    ros::spin();

    return 0;
}
