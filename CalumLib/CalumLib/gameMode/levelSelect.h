#ifndef LEVEL_SELECT_H
#define LEVEL_SELECT_H

#include "gameMode/gameMode.h"

class LevelSelect : public GameMode
{
	public:
		LevelSelect(const char* levelPath);

		void draw();
};

#endif