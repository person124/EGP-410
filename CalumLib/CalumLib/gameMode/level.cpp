#include "level.h"

#include "globalConst.h"

#include "events/eventSystem.h"
#include "events/eventPickupCoin.h"

#include "gui/guiLevel.h"

#include "pathing/grid.h"
#include "pathing/topMap.h"

#include "units/unitManager.h"
#include "units/unitCoin.h"

#include "utils/ioUtils.h"

#include <string>

Level::Level(const char* levelName)
{
	std::string path = GC::PATH_LEVELS;
	path += '/';
	path += levelName;

	IOUtils::loadGrid(path, mpGrid);

	mpUnits = new UnitManager();

	gpEventSystem->addListener(EVENT_PICKUP_COIN, this);

	createGraph();
	initSpawns();
	populateCoins();

	mpGUI = new GUILevel();

	mScore = 0;
}

Level::~Level()
{
	delete mpUnits;
	delete mpMap;

	gpEventSystem->removeListener(EVENT_PICKUP_COIN, this);
}

void Level::update(double dt)
{
	mpUnits->update(dt);

	mpGUI->update(dt);
}

void Level::draw()
{
	mpGrid->draw();

	mpUnits->draw();

	mpGUI->draw();
}

void Level::addScore(int s)
{
	mScore += s;

	((GUILevel*)mpGUI)->setScore(mScore);
}

void Level::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_PICKUP_COIN)
	{
		mCurrentCoins--;
		addScore(25);
	}
}

void Level::createGraph()
{
	mpMap = new TopMap(mpGrid);
	mpMap->generateNodes();
}

void Level::initSpawns()
{
	std::vector<SpawnLocation> spawns = mpGrid->getSpawnLocations();

	for (unsigned int i = 0; i < spawns.size(); i++)
	{
		SpawnLocation* s = &spawns.at(i);
		switch (s->type)
		{
			case PLAYER:
				mpUnits->addPlayer(s->x, s->y);
				break;
			case ENEMY_BLUE:
			case ENEMY_RED:
			case ENEMY_YELLOW:
				mpUnits->addSheerHeartAttack(s->x, s->y, s->type - 1);
				break;
			case CANDY:
				mpUnits->addCandy(s->x, s->y);
				break;
		}
	}
}

void Level::populateCoins()
{
	std::vector<SpawnLocation> spawns = mpGrid->getSpawnLocations();
	int total = 0;
	int width = mpGrid->getWidth();
	int height = mpGrid->getHeight();

	//Change to be random placement
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			bool even = (x % 2 == 0) && (y % 2 == 1);

			if (even && !mpGrid->isSolid(x, y))
			{
				mpUnits->addCoin(x, y);
				total++;
			}
		}

	mTotalCoins = total;
	mCurrentCoins = total;
}