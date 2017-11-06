#include "hud.h"

#include "game.h"
#include "graphics/graphicsSystem.h"

HUD::HUD()
{
	mpFont = new Font(15, "assets/cour.ttf");
	mpFontColor = new Color(1.0f, 1.0f, 1.0f);
}

HUD::~HUD()
{
	delete mpFont;
	delete mpFontColor;
}

void HUD::update(int lives, int score, float fps)
{
}

void HUD::drawFPS()
{
	//TODO
	//Game::pInstance->getGraphics()->writeText(0, 585, *mpFont, *mpFontColor, mStrFPS);
}