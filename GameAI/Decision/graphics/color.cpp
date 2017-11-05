#include "color.h"

Color::Color(int r, int g, int b)
{
	mColor = al_map_rgb(r, g, b);
}

Color::Color(float r, float g, float b)
{
	mColor = al_map_rgb_f(r, g, b);
}

Color::~Color()
{
}

void Color::setAlpha(int a)
{
	setAlpha(a / 255.0f);
}

void Color::setAlpha(float a)
{
	mColor.a = a;
}