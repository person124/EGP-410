#include "movementSHA.h"

#include "stateTree/states/statesSHA.h"

#include "units/unitSHA.h"

void moveSHA::calculateMovement(UnitSHA* unit)
{
	switch (unit->getCurrentState())
	{
		case shaSearching:
			break;
		case shaFleeing:
			break;
		case shaTracking:
			break;
		case shaDead:
			break;
		default:
			break;
	}
}