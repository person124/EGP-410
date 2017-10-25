#include "GameValueTypes.h"

#include <allegro5\keycodes.h>

const std::string MOD_GUI_STRING[MOD_NUM_TYPES] =
{
	"(P)layer Speed: ",
	"(C)ohesion: ",
	"(S)eperation: ",
	"Group (A)lignment: ",
	"(M)ax NPC Speed: ",
	"Ma(X) NPC Accel: ",
	"NPC Ang(U)lar Speed: "
};

const int MOD_KEYCODES[MOD_NUM_TYPES] =
{
	//Can't use keys: F I D TAB O = - ESCAPE SPACEBAR / Z
	ALLEGRO_KEY_P,
	ALLEGRO_KEY_C,
	ALLEGRO_KEY_S,
	ALLEGRO_KEY_A,
	ALLEGRO_KEY_M,
	ALLEGRO_KEY_X,
	ALLEGRO_KEY_U
};

const Value MOD_VALUES[MOD_NUM_TYPES] =
{
	Value(200, 50, 50, 1000),
	Value(0, 0, 0, 0), //Cohesion
	Value(0, 0, 0, 0), //Seperation
	Value(0, 0, 0, 0), //Alignment
	Value(0, 0, 0, 0), //NPC Speed
	Value(0, 0, 0, 0), //NPC Accel
	Value(0, 0, 0, 0) //NPC Angular Speed
};