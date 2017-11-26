#ifndef UNIT_PLAYER_H
#define UNIT_PLAYER_H

#include "events/eventListener.h"

#include "units/unitDirectional.h"

class UnitPlayer : public UnitDirectional, public EventListener
{
	public:
		UnitPlayer(int x, int y);
		~UnitPlayer();

		void update(double dt);

		void handleEvent(const Event& theEvent);
};

#endif