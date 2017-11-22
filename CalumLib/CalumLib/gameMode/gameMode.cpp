#include "gameMode.h"

#include "gui/gui.h"

#include "pathing/grid.h"

GameMode::GameMode()
{
	mpGUI = NULL;
	mpGrid = NULL;
}

GameMode::~GameMode()
{
	if (mpGUI != NULL)
		delete mpGUI;
	if (mpGrid != NULL)
		delete mpGrid;
}