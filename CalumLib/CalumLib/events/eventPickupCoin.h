#ifndef EVENT_PICKUP_COIN_H
#define EVENT_PICKUP_COIN_H

#include "events/event.h"

class EventPickupCoin : public Event
{
	public:
		EventPickupCoin() : Event(EVENT_PICKUP_COIN) {};
		~EventPickupCoin() {};
};

#endif