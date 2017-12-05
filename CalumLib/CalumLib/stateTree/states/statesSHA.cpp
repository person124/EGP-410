#include "statesSHA.h"

#include "game.h"

#include "physics/raycast.h"

#include "stateTree/stateTreeSHA.h"

#include "units/unitPlayer.h"

#include "utils/timer.h"

#include <stdio.h>

int StatesSHA::searching(StateTree* tree, double dt)
{
	StateTreeSHA* shaTree = (StateTreeSHA*)tree;

	//Look for player, until then just wander
	Vector2 unit = shaTree->getUnit()->getPosition();
	Vector2 player = shaTree->getPlayer()->getPosition();

	if (RayCast(Game::pInstance->getCurrentGrid(), unit, player))
	{
		printf("%i\n", player.x);
	}
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