#include "ConverterNode.h"

ConverterNode::ConverterNode()
{
    skeleton_sub=nh.subscribe<skeleton_markers::Skeleton>("skeleton", 1, &ConverterNode::converter_cb, this);
    hand_location_pub=nh.advertise<ocular::HandLoc>("hand_location", 1);

}

void ConverterNode::converter_cb(const skeleton_markers::SkeletonConstPtr & msg)
{
    hand_location_pub.publish(converterObject.handCoordinatesExtractor(*msg));

}
