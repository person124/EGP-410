#include "help.h"

#include "gui/guiHelp.h"

Help::Help()
{
	mpGUI = new GUIHelp();
}

Help::~Help()
{
}

void Help::draw()
{
	mpGUI->draw();
}