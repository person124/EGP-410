#include "guiFixedText.h"

#include "game.h"

#include "graphics/graphicsSystem.h"

GUIFixedText::GUIFixedText(int x, int y, const std::string& text)
{
	mX = x;
	mY = y;
	mText = text;
}

GUIFixedText::~GUIFixedText()
{
}

void GUIFixedText::draw()
{
	Game::pInstance->getGraphics()->writeText(mX, mY, mText);
}