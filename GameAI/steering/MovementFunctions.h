#ifndef MOVEMENT_FUNCTIONS_H
#define MOVEMENT_FUNCTIONS_H

#include "Phys.h"

class UnitSlottable;

namespace slot {
	WeightB seekPlayerWithinRange(UnitSlottable* unit);
	WeightB fleePlayerWithinRange(UnitSlottable* unit);

	WeightB wander(UnitSlottable* unit);

	WeightB avoid(UnitSlottable* unit);
};

#endif