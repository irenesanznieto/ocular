#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include <pcl/point_types.h>
#include <pi_tracker/Skeleton.h>
#include <TFG/EventHandler.h>


class EventHandler
{
public:
    EventHandler();
    TFG::EventHandler select_event_hand(const pi_tracker::SkeletonConstPtr & );

private:
    std::string last_event;

};

#endif // EVENTHANDLER_H
