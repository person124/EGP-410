#include "color.h"

#include <allegro5/allegro_color.h>

Color::Color(int r, int g, int b)
{
	mColor = new ALLEGRO_COLOR(al_map_rgb(r, g, b));
}

Color::Color(float r, float g, float b)
{
	mColor = new ALLEGRO_COLOR(al_map_rgb(r, g, b));
}

Color::~Color()
{
	delete mColor;
}

void Color::setAlpha(int a)
{
	setAlpha(a / 255.0f);
}

void Color::setAlpha(float a)
{
	mColor->a = a;
}