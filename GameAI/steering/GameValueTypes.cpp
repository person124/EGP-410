#include "GameValueTypes.h"

const std::string MOD_GUI_STRING[MOD_NUM_TYPES] =
{
	"Enemy (V)elocity:",
	"Enemy Accel(E)ration:",
	"Reaction (R)adius:",
	"(A)ngular Velocity:",
	"Av(O)id Radius:",
	"(W)ander Circle:",
	"Wa(N)der Rate:",
	"(W)all Avoid Look:",
	"Wa(L)l Avoid Distance:",
	"(P)layer Speed:",
	"Wall Detection Type(:)"
};

const int MOD_KEYCODES[MOD_NUM_TYPES] =
{
	//Can't use keys: C D S F I - = ESCAPE SPACEBAR
	ALLEGRO_KEY_V,
	ALLEGRO_KEY_E,
	ALLEGRO_KEY_R,
	ALLEGRO_KEY_A,
	ALLEGRO_KEY_O,
	ALLEGRO_KEY_W,
	ALLEGRO_KEY_N,
	ALLEGRO_KEY_W,
	ALLEGRO_KEY_L,
	ALLEGRO_KEY_P,
	ALLEGRO_KEY_SEMICOLON
};

const Value MOD_VALUES[MOD_NUM_TYPES] =
{
	Value(100, 10, 10, 600), //Enemy Velocity
	Value(150, 25, 25, 500), //Enemy Acceleration
	Value(175, 5, 10, 500), //Enemy Reaction Radius
	Value(1.5, 0.5, 0, 400), //Angular Speed
	Value(120, 15, 15, 500), //Avoid Radius
	Value(150, 25, 25, 300), //Wander Circle
	Value(3.15f, 0.15f, 0.15f, 6.3f), //Wander Rate
	Value(75, 15, 15, 390), //Wall avoid look
	Value(250, 50, 200, 1500), //Wall avoid dist
	Value(300, 25, 25, 800), //Player Speed
	//0 for bounce, 1 for flee, 2 for seek
	Value(0, 1, 0, 2) //Wall detection type
};