#include "GameValueTypes.h"

#include <allegro5\keycodes.h>

const std::string MOD_GUI_STRING[MOD_NUM_TYPES] =
{
	"NPC Sp(R)ead: ",
	"Display D(E)bug: ",
	"(C)ohesion: ",
	"(S)eperation: ",
	"Group (A)lignment: ",
	"(M)ax NPC Speed: ",
	"Ma(X) NPC Accel: ",
	"NPC Ang(U)lar Speed: ",
	"(W)ander Offset: ",
	"Wa(N)der Radius: "
};

const int MOD_KEYCODES[MOD_NUM_TYPES] =
{
	//Can't use keys: F I D TAB O = - ESCAPE SPACEBAR / Z
	ALLEGRO_KEY_R,
	ALLEGRO_KEY_E,
	ALLEGRO_KEY_C,
	ALLEGRO_KEY_S,
	ALLEGRO_KEY_A,
	ALLEGRO_KEY_M,
	ALLEGRO_KEY_X,
	ALLEGRO_KEY_U,
	ALLEGRO_KEY_W,
	ALLEGRO_KEY_N
};

const Value MOD_VALUES[MOD_NUM_TYPES] =
{
	Value(25, 25, 25, 200), //NPC Spread
	Value(0, 1, 0, 1), //Display Debug
	Value(0, 0, 0, 0), //Cohesion
	Value(0, 0, 0, 0), //Seperation
	Value(0, 0, 0, 0), //Alignment
	Value(150, 25, 0, 500), //NPC Speed
	Value(150, 25, 0, 500), //NPC Accel
	Value(2.5f, 0.5f, 0, 6), //NPC Angular Speed
	Value(150, 25, 25, 350), //Wander Offset
	Value(60, 10, 10, 350) //Wander Radius
};