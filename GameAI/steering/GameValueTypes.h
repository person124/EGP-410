#ifndef GAME_VALUE_TYPES_H
#define GAME_VALUE_TYPES_H

#include <allegro5\keycodes.h>
#include <string>

struct Value
{
	Value(float value, float a, float minValue, float maxValue)
	{
		starting = value;
		adjust = a;
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
	MOD_NPC_SPEED,
	MOD_NPC_ACCEL,
	MOD_NPC_REACT,
	MOD_NPC_ANGULAR, //TODO NOT USED
	MOD_NPC_AVOID,
	MOD_NPC_WANDER_CIRCLE,
	MOD_NPC_WANDER_RATE,
	MOD_NPC_WALL_LOOK,
	MOD_NPC_WALL_DIST,
	MOD_PLAYER_SPEED,
	MOD_WALL_TYPE,
	MOD_NUM_TYPES
};

extern const std::string MOD_GUI_STRING[MOD_NUM_TYPES];
extern const int MOD_KEYCODES[MOD_NUM_TYPES];
extern const Value MOD_VALUES[MOD_NUM_TYPES];

#endif