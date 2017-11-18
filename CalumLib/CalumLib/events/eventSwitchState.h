#ifndef EVENT_SWITCH_STATE_H
#define EVENT_SWITCH_STATE_H

#include "events/event.h"

enum GameState
{
	STATE_MAIN_MENU,
	STATE_IN_GAME,
	STATE_OPTIONS,
	STATE_EDITOR
};

class EventSwitchState : public Event
{
	public:
		EventSwitchState(GameState state) : Event(EVENT_SWITCH_STATE) { mState = state; };
		~EventSwitchState() {};

		GameState getState() const { return mState; };
	private:
		GameState mState;
};

#endif