#ifndef EVENT_ADD_AI_H
#define EVENT_ADD_AI_H

#include "Event.h"

class EventAddAI : public Event
{
	public:
		EventAddAI(bool isFlee) :Event(EVENT_ADD_AI) { mIsFlee = isFlee; };
		~EventAddAI() {};

		bool isArrive() const { return mIsFlee; };
	private:
		bool mIsFlee;
};

#endif