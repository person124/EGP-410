#ifndef LEVEL_H
#define LEVEL_H

#include "events/eventListener.h"

#include "gameMode/gameMode.h"

class Grid;
class UnitManager;

class Level : public GameMode, public EventListener
{
	public:
		Level(const char* levelName);
		~Level();

		void update(double dt);
		void draw();

		UnitManager* getUnits() { return mpUnits; };

		void handleEvent(const Event& theEvent);
	private:
		void createGraph();
		void initSpawns();
		void populateCoins();

		UnitManager* mpUnits;

		int mTotalCoins, mCurrentCoins;
};

#endif