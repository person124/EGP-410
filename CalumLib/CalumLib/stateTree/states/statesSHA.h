#ifndef STATES_SHA_H
#define STATES_SHA_H

#include "stateTree/state.h"

enum StatesSHAID
{
	shaSearching = 0,
	shaFleeing,
	shaTracking,
	shaDead,
	sha_STATE_COUNT
};

class StateTreeSHA;

namespace StatesSHA
{
	int searching(StateTree* tree, double dt);
	int fleeing(StateTree* tree, double dt);
	int tracking(StateTree* tree, double dt);
	int dead(StateTree* tree, double dt);
}

#endif