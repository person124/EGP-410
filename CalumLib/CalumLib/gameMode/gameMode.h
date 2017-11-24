#ifndef GAME_MODE_H
#define GAME_MODE_H

#include "utils/trackable.h"

class GUI;
class Grid;

class GameMode : public Trackable
{
	public:
		GameMode();
		virtual ~GameMode();

		virtual void update(double dt) {};
		virtual void draw() {};
	protected:
		GUI* mpGUI;
		Grid* mpGrid;
};

#endif