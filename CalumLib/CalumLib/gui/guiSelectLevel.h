#ifndef GUI_SELECT_LEVEL_H
#define GUI_SELECT_LEVEL_H

#include "gui/guiSelectable.h"

class GUISelectLevel : public GUISelectable
{
	public:
		GUISelectLevel(const char* levelPath);
};

#endif