#include "statesSHA.h"

int StatesSHA::searching(double dt)
{
	//Look for player
	return shaSearching;
}

int StatesSHA::fleeing(double dt)
{
	//Wait for player's invincible state to end
	return shaFleeing;
}

int StatesSHA::tracking(double dt)
{
	//Wait until line of sight is lost for a few seconds
	return shaTracking;
}

int StatesSHA::dead(double dt)
{
	//Wait 10 seconds then switch to searching
	return shaDead;
}