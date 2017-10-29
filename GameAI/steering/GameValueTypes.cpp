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
	"Wa(N)der Radius: ",
	"Wa(L)l Cast Distance: ",
	"Wall Seek(P)oint Distance: ",
	"Co(H)esion Effect Distance: ",
	"Sepera(T)ion Effect Distance: ",
	"Seperation Deca(Y) in 1K: ",
	"Face Distance(:) ",
	"(V)el. Match Distance: "
};

const int MOD_KEYCODES[MOD_NUM_TYPES] =
{
	//Can't use keys: F I D TAB O = - ESCAPE SPACEBAR / Z LCTRL
	ALLEGRO_KEY_R,
	ALLEGRO_KEY_E,
	ALLEGRO_KEY_C,
	ALLEGRO_KEY_S,
	ALLEGRO_KEY_A,
	ALLEGRO_KEY_M,
	ALLEGRO_KEY_X,
	ALLEGRO_KEY_U,
	ALLEGRO_KEY_W,
	ALLEGRO_KEY_N,
	ALLEGRO_KEY_L,
	ALLEGRO_KEY_P,
	ALLEGRO_KEY_H,
	ALLEGRO_KEY_T,
	ALLEGRO_KEY_Y,
	ALLEGRO_KEY_SEMICOLON,
	ALLEGRO_KEY_V
};

const Value MOD_VALUES[MOD_NUM_TYPES] =
{
	Value(25, 25, 25, 200), //NPC Spread
	Value(0, 1, 0, 5), //Display Debug
	Value(0.75f, 0.25f, 0, 2), //Cohesion
	Value(1.25f, 0.25f, 0, 2), //Seperation
	Value(1, 0.25f, 0, 2), //Alignment
	Value(150, 25, 0, 500), //NPC Speed
	Value(150, 25, 0, 500), //NPC Accel
	Value(2.5f, 0.5f, 0, 6), //NPC Angular Speed
	Value(150, 25, 25, 350), //Wander Offset
	Value(60, 10, 10, 350), //Wander Radius
	Value(100, 25, 25, 500), //Wall raycast size
	Value(150, 25, 25, 500), //Wall seek target distance
	Value(150, 25, 25, 600), //Cohesion distance
	Value(75, 25, 25, 600), //Seperation distance
	Value(100, 10, 0, 300), //Seperation decay
	Value(150, 25, 25, 500), //Face threshold distance
	Value(150, 25, 25, 500) //Velocity match threshold distance
};