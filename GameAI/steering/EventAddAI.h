#ifndef EVENT_ADD_AI_H
#define EVENT_ADD_AI_H

#include "Event.h"

class EventAddAI : public Event
{
	public:
		EventAddAI(bool cluster) :Event(EVENT_ADD_AI) { mCluster = cluster; };
		~EventAddAI() {};

		bool spawnCluster() const { return mCluster; };
	private:
		bool mCluster;
};

#endif