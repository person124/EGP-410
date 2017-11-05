#include "hud.h"

#include "../game.h"
#include "graphicsSystem.h"

Hud::Hud()
{
	mpFont = new Font(15, "assets/cour.ttf");
	mpFontColor = new Color(1.0f, 1.0f, 1.0f);
}

Hud::~Hud()
{
	delete mpFont;
	delete mpFontColor;
}

void Hud::update(int lives, int score, float fps)
{
}

void Hud::drawFPS()
{
	//TODO
	//Game::pInstance->getGraphics()->writeText(0, 585, *mpFont, *mpFontColor, mStrFPS);
}