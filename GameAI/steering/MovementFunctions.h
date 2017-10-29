#ifndef MOVEMENT_FUNCTIONS_H
#define MOVEMENT_FUNCTIONS_H

#include "Phys.h"

class UnitSlottable;

namespace slot {
	WeightB wander(UnitSlottable* unit);

	WeightB wallAvoid(UnitSlottable* unit);

	WeightB face(UnitSlottable* unit);
};

#endif