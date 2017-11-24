#ifndef GUI_SELECT_LEVEL_H
#define GUI_SELECT_LEVEL_H

#include "gui/guiSelectable.h"

#include <string>

class GUISelectLevel : public GUISelectable
{
	public:
		GUISelectLevel(const char* levelPath);
		~GUISelectLevel();
	private:
		std::string* mpLevels;
};

#endif