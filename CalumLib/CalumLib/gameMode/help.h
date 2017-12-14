#ifndef HELP_H
#define HELP_H

#include "gameMode/gameMode.h"

class Help : public GameMode
{
	public:
		Help();
		~Help();

		void draw();
};

#endif