#ifndef GAME_VALUE_TYPES_H
#define GAME_VALUE_TYPES_H

#include <allegro5\keycodes.h>
#include <string>

enum ModifyValues
{
	MOD_INVALID = -1,
	MOD_VELOCITY,
	MOD_REACTION_RADIUS,
	MOD_ANGULAR_SPEED,
	MOD_AVOID_RADIUS,
	MOD_PLAYER_SPEED,
	MOD_NUM_TYPES
};

const std::string MOD_GUI_STRING[MOD_NUM_TYPES] =
{
	"Enemy (V)elocity:",
	"Reaction (R)adius:",
	"(A)ngular Velocity:",
	"Av(O)id Radius:",
	"(P)layer Speed:"
};

const int MOD_KEYCODES[MOD_NUM_TYPES] = 
{
	ALLEGRO_KEY_V,
	ALLEGRO_KEY_R,
	ALLEGRO_KEY_A,
	ALLEGRO_KEY_O,
	ALLEGRO_KEY_P
};

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

const Value MOD_VALUES[MOD_NUM_TYPES] =
{
	Value(10, 0.5, 0, 400), //Enemy Velocity
	Value(175, 5, 10, 500), //Reaction Radius
	Value(10, 0.5, 0, 400), //Angular Speed
	Value(125, 15, 15, 500), //Avoid Radius
	Value(300, 25, 25, 800) //Player Speed
};

#endif