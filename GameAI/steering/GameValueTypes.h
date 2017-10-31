#ifndef GAME_VALUE_TYPES_H
#define GAME_VALUE_TYPES_H

#include <string>

struct Value
{
	Value(float value, float modifyAmount, float minValue, float maxValue)
	{
		starting = value;
		adjust = modifyAmount;
		min = minValue;
		max = maxValue;
	};
	float starting;
	float adjust;
	float min;
	float max;

	void check(float& value) const
	{
		if (value < min)
			value = min;
		if (value > max)
			value = max;
	}
};

enum ModifyValues
{
	MOD_INVALID = -1,
	MOD_UNIT_SIZE,
	MOD_SPREAD,
	MOD_DISPLAY_TIPS,
	MOD_COHESION,
	MOD_SEPERATION,
	MOD_ALIGNMENT,
	MOD_WANDER,
	MOD_SPEED,
	MOD_ACCEL,
	MOD_ANGULAR,
	MOD_WANDER_OFFSET,
	MOD_WANDER_RADIUS,
	MOD_WALL_CAST,
	MOD_WALL_SEEK,
	MOD_COHESION_DISTANCE,
	MOD_SEPERATION_THRESHOLD,
	MOD_SEPERATION_DECAY,
	MOD_FACE_THRESHOLD,
	MOD_VELOCITY_THRESHOLD,
	MOD_WALL_ENABLED,
	MOD_NUM_TYPES
};

extern const std::string MOD_GUI_STRING[MOD_NUM_TYPES];
extern const int MOD_KEYCODES[MOD_NUM_TYPES];
extern const Value MOD_VALUES[MOD_NUM_TYPES];

#endif