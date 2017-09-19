#ifndef EVENT_ADD_AI_H
#define EVENT_ADD_AI_H

#include "Event.h"

class EventAddAI : public Event
{
	public:
		EventAddAI(bool isArrive) :Event(EVENT_ADD_AI) { mIsArrive = isArrive; };
		~EventAddAI() {};

		bool isArrive() const { return mIsArrive; };
	private:
		bool mIsArrive;
};

#endif