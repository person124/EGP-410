#ifndef LEVEL_H
#define LEVEL_H

#include "events/eventListener.h"

#include "gameMode/gameMode.h"

#include <vector>

class UnitManager;
class TopMap;
struct Node;

class Level : public GameMode, public EventListener
{
	public:
		Level(const char* levelName);
		~Level();

		void update(const double& dt);
		void draw();

		void addScore(int s);
		int getScore() { return mScore; };

		UnitManager* getUnits() { return mpUnits; };
		std::vector<Node*> getPath(int startX, int startY, int endX, int endY);

		void handleEvent(const Event& theEvent);

		bool isDebugOn() { return mDebug; };
	private:
		void createGraph();
		void initSpawns();
		void populateCoins();

		UnitManager* mpUnits;
		int mScore;

		int mTotalCoins, mCurrentCoins;

		TopMap* mpMap;

		bool mDebug;
};

#endif