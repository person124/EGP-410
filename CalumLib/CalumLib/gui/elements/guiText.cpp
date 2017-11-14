#include "guiText.h"

#include "game.h"

#include "graphics/graphicsSystem.h"

GUIText::GUIText(int x, int y, const std::string& text) : GUIFixedText(x, y, text)
{
}

GUIText::GUIText(int x, int y) : GUIFixedText(x, y, "")
{
}

GUIText::~GUIText()
{
}

void GUIText::updateText(const std::string& text)
{
	mText = text;
}

void GUIText::updateText(const char* text)
{
	mText = text;
}