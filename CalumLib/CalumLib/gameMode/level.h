#ifndef LEVEL_H
#define LEVEL_H

#include "gameMode/gameMode.h"

class Grid;
class UnitManager;

class Level : public GameMode
{
	public:
		Level(const char* levelName);
		~Level();

		void update(double dt);
		void draw();

		UnitManager* getUnits() { return mpUnits; };
	private:
		void createGraph();
		void initSpawns();
		void populateCoins();

		UnitManager* mpUnits;
};

#endif