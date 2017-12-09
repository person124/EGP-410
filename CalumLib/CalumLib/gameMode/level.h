#ifndef LEVEL_H
#define LEVEL_H

#include "events/eventListener.h"

#include "gameMode/gameMode.h"

class UnitManager;
class TopMap;

class Level : public GameMode, public EventListener
{
	public:
		Level(const char* levelName);
		~Level();

		void update(double dt);
		void draw();

		void addScore(int s);

		UnitManager* getUnits() { return mpUnits; };

		void handleEvent(const Event& theEvent);
	private:
		void createGraph();
		void initSpawns();
		void populateCoins();

		UnitManager* mpUnits;
		int mScore;

		int mTotalCoins, mCurrentCoins;

		TopMap* mpMap;
};

#endif