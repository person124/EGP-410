#include "movementFunctions.h"

#include "physics/weightedBehaviour.h"

#include "units/unitPhys.h"

WeightB move::face(UnitPhys* unit)
{
	SteeringOutput out;

	return WeightB(out, 1.0f);
}

WeightB move::seek(UnitPhys* unit)
{
	SteeringOutput out;

	return WeightB(out, 1.0f);
}
WeightB move::friction(UnitPhys* unit)
{
	return WeightB(SteeringOutput(), 1.0f);
}