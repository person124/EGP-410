#ifndef EVENT_MODIFY_H
#define EVENT_MODIFY_H

#include "Event.h"

class EventModify : public Event
{
	public:
		EventModify(bool increase) :Event(EVENT_MODIFY) { mIncrease = increase; };
		~EventModify() {};

		bool isIncrease() const { return mIncrease; };
	private:
		bool mIncrease;
};

#endif