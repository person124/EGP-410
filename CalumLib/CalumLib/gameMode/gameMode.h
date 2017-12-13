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

		virtual void update(const double& dt) {};
		virtual void draw() {};

		Grid* getGrid() { return mpGrid; };
	protected:
		GUI* mpGUI;
		Grid* mpGrid;
};

#endif