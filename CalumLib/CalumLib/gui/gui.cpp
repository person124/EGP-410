#include "gui.h"

#include "gui/guiElement.h"

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

void GUI::update(double dt)
{
	for (int i = 0; i < mElementCount; i++)
		mpElements[i]->update(dt);
}

void GUI::draw()
{
	for (int i = 0; i < mElementCount; i++)
		mpElements[i]->draw();
}