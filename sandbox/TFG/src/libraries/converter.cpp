#include "converter.h"


Converter::Converter()
{
    input_sub=nh.subscribe<pi_tracker::Skeleton>("/skeleton", 1, &Converter::input_callback, this);
    output_sub=nh.advertise<TFG::HandLoc>("/TFG/hand_loc", 1);
}


void Converter::input_callback(const pi_tracker::SkeletonConstPtr &msg)
{

   TFG::HandLoc hand_location ;

   hand_location.header=msg->header;

   //left_hand --> 5, right_hand --> 8
   hand_location.name[0]=msg->name[5];
   hand_location.name[1]=msg->name[8];
   hand_location.position[0]=msg->position[5];
   hand_location.position[1]=msg->position[8];

   output_sub.publish(hand_location);
}

