#include "converter.h"


Converter::Converter()
{
    input_sub=nh.subscribe<pi_tracker::Skeleton>("input", 1, &Converter::input_callback, this);
    output_sub=nh.advertise<TFG::HandLoc>("output", 1);
}


void Converter::input_callback(const pi_tracker::SkeletonConstPtr &msg)
{

   TFG::HandLoc hand_location;

   hand_location.header=msg->header;
   hand_location.user_id=msg->user_id;
   //left_hand --> 5, right_hand --> 8
   hand_location.name.push_back(msg->name[5]);
   hand_location.name.push_back(msg->name[8]);
   hand_location.position.push_back(msg->position[5]);
   hand_location.position.push_back(msg->position[8]);

   output_sub.publish(hand_location);
}

