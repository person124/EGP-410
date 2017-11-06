#ifndef EVENT_DIJKSTRA_H
#define EVENT_DIJKSTRA_H

#include "events/event.h"

class EventDijkstra : public Event
{
	public:
		EventDijkstra() :Event(EVENT_DIJKSTRA) {};
		~EventDijkstra() {};
};

#endif