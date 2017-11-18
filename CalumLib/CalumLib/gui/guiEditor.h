#ifndef GUI_EDITOR_H
#define GUI_EDITOR_H

#include "gui/gui.h"

class GUIEditor : public GUI
{
	public:
		GUIEditor();

		void changeSelected(int select);

		void setTileFrame(int frame);
		void setSpawnFrame(int frame);
	private:
};

#endif