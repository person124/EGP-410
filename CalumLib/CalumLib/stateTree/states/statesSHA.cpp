#include "statesSHA.h"

#include "stateTree/StateTreeSHA.h"

#include "utils/timer.h"

#include <stdio.h>

int StatesSHA::searching(StateTree* tree, double dt)
{
	//Look for player
	return shaSearching;
}

int StatesSHA::fleeing(StateTree* tree, double dt)
{
	//Wait for player's invincible state to end
	return shaFleeing;
}

int StatesSHA::tracking(StateTree* tree, double dt)
{
	//Wait until line of sight is lost for a few seconds
	return shaTracking;
}

int StatesSHA::dead(StateTree* tree, double dt)
{
	//Wait 10 seconds then switch to searching
	StateTreeSHA* shaTree = (StateTreeSHA*)tree;

	if (shaTree->getTimer()->getElapsedTime() >= 10)
		return shaSearching;

	return shaDead;
}