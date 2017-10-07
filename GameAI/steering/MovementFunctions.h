#ifndef MOVEMENT_FUNCTIONS_H
#define MOVEMENT_FUNCTIONS_H

#include "Phys.h"

class UnitSlottable;

SteeringOutput arrive(Vector2& target, UnitSlottable* unit, bool flee);
WeightB arriveOrFlee(UnitSlottable* unit, bool flee);

WeightB arrivePlayerWithinRange(UnitSlottable* unit);
WeightB fleePlayerWithinRange(UnitSlottable* unit);
WeightB wander(UnitSlottable* unit);

#endif