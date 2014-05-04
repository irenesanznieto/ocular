#include "ConverterNode.h"

ConverterNode::ConverterNode()
{
    skeleton_sub=nh.subscribe<pi_tracker::Skeleton>("skeleton", 1, &ConverterNode::converter_cb, this);
    hand_location_pub=nh.advertise<ocular::HandLoc>("hand_location", 1);

}

void ConverterNode::converter_cb(const pi_tracker::SkeletonConstPtr & msg)
{
    hand_location_pub.publish(converterObject.handCoordinatesExtractor(*msg));

}
