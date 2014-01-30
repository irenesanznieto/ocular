#ifndef CONVERTER_H
#define CONVERTER_H
#include <ros/ros.h>
#include <pi_tracker/Skeleton.h>
#include "../msg_gen/cpp/include/TFG/HandLoc.h"
#include <std_msgs/String.h>

class Converter 
{
public:
    Converter();
    TFG::HandLoc handCoordinatesExtractor(const pi_tracker::Skeleton &);


private:


};
#endif // CONVERTER_H
