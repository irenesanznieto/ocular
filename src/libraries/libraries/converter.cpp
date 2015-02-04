#include "converter.h"


Converter::Converter()
{}


ocular::HandLoc Converter::handCoordinatesExtractor(const skeleton_markers::Skeleton &msg)
{

   ocular::HandLoc hand_location;

   hand_location.header=msg.header;
   hand_location.user_id=msg.user_id;

   //left_hand --> 5, right_hand --> 8
   hand_location.name.push_back(msg.name[5]);
   hand_location.name.push_back(msg.name[8]);
   hand_location.position.push_back(msg.position[5]);
   hand_location.position.push_back(msg.position[8]);

   return hand_location;
}

