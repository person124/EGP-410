#ifndef EVENT_MODIFY_STAT_H
#define EVENT_MODIFY_STAT_H

#include "Event.h"
#include "GameValueTypes.h"

class EventModifyStat : public Event
{
	public:
		EventModifyStat(ModifyValues value) :Event(EVENT_MODIFY_STAT)
		{
			if (value < 0 || value >= MOD_NUM_TYPES)
				mValue = MOD_INVALID;
			else
				mValue = value;
		};
		~EventModifyStat() {};

		ModifyValues getValue() const { return mValue; };
	private:
		ModifyValues mValue;
};

#endif