#ifndef GAME_VALUE_TYPES_H
#define GAME_VALUE_TYPES_H

#include <allegro5\keycodes.h>
#include <string>

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
	MOD_PLAYER_SPEED,
	MOD_NUM_TYPES
};

const std::string MOD_GUI_STRING[MOD_NUM_TYPES] =
{
	"Enemy (V)elocity:",
	"Enemy Accel(E)ration:",
	"Reaction (R)adius:",
	"(A)ngular Velocity:",
	"Av(O)id Radius:",
	"(W)ander Circle:",
	"Wa(N)der Rate:",
	"(P)layer Speed:"
};

const int MOD_KEYCODES[MOD_NUM_TYPES] = 
{
	//Can't use keys: C D S F I - = ESCAPE
	ALLEGRO_KEY_V,
	ALLEGRO_KEY_E,
	ALLEGRO_KEY_R,
	ALLEGRO_KEY_A,
	ALLEGRO_KEY_O,
	ALLEGRO_KEY_W,
	ALLEGRO_KEY_N,
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
	Value(100, 10, 10, 600), //Enemy Velocity
	Value(150, 25, 25, 500), //Enemy Acceleration
	Value(175, 5, 10, 500), //Enemy Reaction Radius
	Value(10, 0.5, 0, 400), //Angular Speed
	Value(120, 15, 15, 500), //Avoid Radius
	Value(150, 25, 25, 300), //Wander Circle
	Value(3.15f, 0.15f, 0.15f, 6.3f), //Wander Rate
	Value(300, 25, 25, 800) //Player Speed
};

#endif