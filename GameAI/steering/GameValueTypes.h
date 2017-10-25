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
	MOD_NPC_SPREAD,
	MOD_COHESION,
	MOD_SEPERATION,
	MOD_ALIGNMENT,
	MOD_NPC_SPEED,
	MOD_NPC_ACCEL,
	MOD_NPC_ANGULAR,
	MOD_NUM_TYPES
};

extern const std::string MOD_GUI_STRING[MOD_NUM_TYPES];
extern const int MOD_KEYCODES[MOD_NUM_TYPES];
extern const Value MOD_VALUES[MOD_NUM_TYPES];

#endif