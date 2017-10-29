#ifndef MOVEMENT_FUNCTIONS_H
#define MOVEMENT_FUNCTIONS_H

#include "Phys.h"

class UnitSlottable;

namespace slot {
	WeightB wander(UnitSlottable* unit);

	WeightB wallAvoid(UnitSlottable* unit);

	WeightB face(UnitSlottable* unit);

	WeightB matchVelocity(UnitSlottable* unit);
	WeightB seperation(UnitSlottable* unit);
	WeightB cohesion(UnitSlottable* unit);
};

#endif