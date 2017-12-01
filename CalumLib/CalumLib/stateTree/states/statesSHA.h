#ifndef STATES_SHA_H
#define STATES_SHA_H

#include "stateTree/state.h"

enum StatesSHAID
{
	shaSearching = 0,
	shaFleeing,
	shaTracking,
	shaDead
};

namespace StatesSHA
{
	int searching(double dt);
	int fleeing(double dt);
	int tracking(double dt);
	int dead(double dt);
}

#endif