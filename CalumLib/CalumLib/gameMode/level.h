#ifndef LEVEL_H
#define LEVEL_H

#include "gameMode/gameMode.h"

class Grid;
class UnitManager;

class Level : public GameMode
{
	public:
		Level();
		~Level();

		void update(double dt);
		void draw();
	private:
		UnitManager* mpUnits;
};

#endif