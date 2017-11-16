#ifndef STEERING_OUTPUT_H
#define STEERING_OUTPUT_H

#include "physics/vector2.h"

struct SteeringOutput
{
	Vector2 linear;
	float angular;
};

#endif