#ifndef UNIT_PLAYER_H
#define UNIT_PLAYER_H

#include "Unit.h"
#include "EventListener.h"

class UnitPlayer : public Unit, public EventListener
{
	public:
		UnitPlayer();
		virtual ~UnitPlayer();
		void update(float dt);

		void handleEvent(const Event& theEvent);
	private:
		Vector2 mTarget;
};

#endif