#include "gui.h"

#include "gui/guiElement.h"
#include "gui/guiText.h"

GUI::GUI()
{
	mElementCount = 0;
	mpElements = NULL;
}

GUI::~GUI()
{
	for (int i = 0; i < mElementCount; i++)
		delete mpElements[i];
	delete[] mpElements;
}

void GUI::draw()
{
	for (int i = 0; i < mElementCount; i++)
		mpElements[i]->draw();
}