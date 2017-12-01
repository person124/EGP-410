#include "StateTreeSHA.h"

#include "stateTree/state.h"
#include "stateTree/states/StatesSHA.h"

StateTreeSHA::StateTreeSHA()
{
	mSize = 5;
	mpStates = new State[5];

	mpStates[shaSearching] = State(shaSearching, StatesSHA::searching);
	mpStates[shaFleeing] = State(shaFleeing, StatesSHA::fleeing);
	mpStates[shaTracking] = State(shaTracking, StatesSHA::tracking);
	mpStates[shaDead] = State(shaDead, StatesSHA::dead);

	mpCurrentState = &mpStates[0];
}

StateTreeSHA::~StateTreeSHA()
{
}