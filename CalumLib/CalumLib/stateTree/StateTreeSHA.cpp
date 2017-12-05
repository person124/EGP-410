#include "stateTreeSHA.h"

#include "game.h"

#include "gameMode/level.h"

#include "stateTree/state.h"
#include "stateTree/states/statesSHA.h"

#include "units/unitManager.h"

#include "utils/timer.h"

StateTreeSHA::StateTreeSHA(Unit* unit) : StateTree(unit)
{
	mSize = 5;
	mpStates = new State[sha_STATE_COUNT];

	mpStates[shaSearching] = State(shaSearching, StatesSHA::searching);
	mpStates[shaFleeing] = State(shaFleeing, StatesSHA::fleeing);
	mpStates[shaTracking] = State(shaTracking, StatesSHA::tracking);
	mpStates[shaDead] = State(shaDead, StatesSHA::dead);

	mpTimer = new Timer();

	transfer(shaSearching);
}

StateTreeSHA::~StateTreeSHA()
{
	delete mpTimer;
}

void StateTreeSHA::transfer(int state)
{
	switch (state)
	{
		case shaDead:
			mpTimer->start();
			break;
		case shaSearching:
			mpTimer->stop();
			break;
		default:
			break;
	}

	if (state < 0 || state >= sha_STATE_COUNT)
		return;
	mpCurrentState = &mpStates[state];
}

UnitPlayer* StateTreeSHA::getPlayer()
{
	return ((Level*)Game::pInstance->getCurrentMode())->getUnits()->getPlayer();
}