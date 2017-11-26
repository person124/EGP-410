#ifndef STEERING_OUTPUT_H
#define STEERING_OUTPUT_H

#include "physics/vector2.h"

struct SteeringOutput
{
	SteeringOutput()
	{
		linear.x = 0;
		linear.y = 0;
		angular = 0;
	}
	Vector2 linear;
	float angular;
};

#endif