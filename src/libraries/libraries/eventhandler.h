#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include <pcl/point_types.h>
#include <pi_tracker/Skeleton.h>
#include <ocular/EventHandler.h>


class EventHandler
{
public:
    EventHandler();
    ocular::EventHandler select_event_hand( pi_tracker::Skeleton );

private:
    std::string last_event;

};

#endif // EVENTHANDLER_H
