#ifndef EVENT_MODIFY_STAT_H
#define EVENT_MODIFY_STAT_H

#include "Event.h"

enum ModifyValues
{
	MOD_INVALID = -1,
	MOD_VELOCITY,
	MOD_REACTION_RADIUS,
	MOD_ANGULAR_SPEED,
	MOD_NUM_TYPES
};

class EventModifyStat : public Event
{
	public:
		EventModifyStat(ModifyValues value) :Event(EVENT_MODIFY)
		{
			if (value < 0 || value > MOD_NUM_TYPES)
				mValue = MOD_INVALID;
			else
				mValue = value;
		};
		~EventModifyStat() {};

		ModifyValues getValue() { return mValue; };
	private:
		ModifyValues mValue;
};

#endif