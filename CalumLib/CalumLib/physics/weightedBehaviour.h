#ifndef WEIGHTED_BEHAVIOUR_H
#define WEIGHTED_BEHAVIOUR_H

#include "physics/steeringOutput.h"

struct WeightB
{
	WeightB(SteeringOutput steer, float w)
	{
		steering = steer;
		weight = w;
	}
	SteeringOutput steering;
	float weight;
};

#endif