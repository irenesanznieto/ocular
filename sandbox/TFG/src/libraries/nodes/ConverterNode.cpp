#include "ConverterNode.h"

ConverterNode::ConverterNode()
{
    input_sub=nh.subscribe<pi_tracker::Skeleton>("input", 1, &Converter::converter_cb, this);
    output_sub=nh.advertise<TFG::HandLoc>("output", 1);

}

void ConverterNode::converter_cb(const pi_tracker::SkeletonConstPtr & msg)
{
    output_sub.publish(converterObject.handCoordinatesExtractor(msg.get()));

}
