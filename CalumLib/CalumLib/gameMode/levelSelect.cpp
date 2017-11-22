#include "levelSelect.h"

#include "gui/guiSelectLevel.h"

LevelSelect::LevelSelect(const char* levelPath)
{
	mpGUI = new GUISelectLevel(levelPath);
}

void LevelSelect::draw()
{
	mpGUI->draw();
}