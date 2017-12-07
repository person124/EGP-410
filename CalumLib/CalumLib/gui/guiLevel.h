#ifndef GUI_LEVEL_H
#define GUI_LEVEL_H

#include "gui/gui.h"

class GUILevel : public GUI
{
	public:
		GUILevel();
		~GUILevel();

		void setScore(int s);
};

#endif