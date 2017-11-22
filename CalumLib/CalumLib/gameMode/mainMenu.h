#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "gameMode/gameMode.h"

class MainMenu : public GameMode
{
	public:
		MainMenu();

		void draw();
};

#endif