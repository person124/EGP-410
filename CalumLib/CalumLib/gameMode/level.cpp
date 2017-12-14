#include "level.h"

#include "game.h"
#include "globalConst.h"

#include "events/eventSystem.h"
#include "events/eventPickupCoin.h"
#include "events/eventKeypress.h"

#include "graphics/graphicsSystem.h"

#include "gui/guiLevel.h"

#include "pathing/grid.h"
#include "pathing/topMap.h"

#include "units/unitManager.h"
#include "units/unitCoin.h"

#include "utils/ioUtils.h"

#include <string>
#include <assert.h>

Level::Level(const char* levelName)
{
	std::string path = GC::PATH_LEVELS;
	path += '/';
	path += levelName;

	IOUtils::loadGrid(path, mpGrid);

	mpUnits = new UnitManager();

	gpEventSystem->addListener(EVENT_PICKUP_COIN, this);
	gpEventSystem->addListener(EVENT_KEYPRESS, this);

	createGraph();
	initSpawns();
	populateCoins();

	mpGUI = new GUILevel();

	mScore = 0;

	mDebug = false;
}

Level::~Level()
{
	delete mpUnits;
	delete mpMap;

	gpEventSystem->removeListener(EVENT_PICKUP_COIN, this);
	gpEventSystem->removeListener(EVENT_KEYPRESS, this);
}

void Level::update(const double& dt)
{
	mpUnits->update(dt);

	mpGUI->update(dt);
}

void Level::draw()
{
	if (!mDebug)
		mpGrid->draw();
	else
		mpGrid->drawSolidity();

	mpUnits->draw();

	mpGUI->draw();
}

void Level::addScore(int s)
{
	mScore += s;

	((GUILevel*)mpGUI)->setScore(mScore);
}

std::vector<Node*> Level::getPath(int startX, int startY, int endX, int endY)
{
	return mpMap->getPath(startX, startY, endX, endY);
}

void Level::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_PICKUP_COIN)
	{
		mCurrentCoins--;
		addScore(25);
	}
	else if (theEvent.getType() == EVENT_KEYPRESS)
	{
		const EventKeypress& e = static_cast<const EventKeypress&>(theEvent);

		if (e.getKey() == KEYS_TOGGLE_SOLIDITY)
			mDebug = !mDebug;
	}
}

void Level::createGraph()
{
	mpMap = new TopMap(mpGrid);
}

void Level::initSpawns()
{
	std::vector<SpawnLocation> spawns = mpGrid->getSpawnLocations();
	bool foundPlayer = false;

	for (unsigned int i = 0; i < spawns.size(); i++)
	{
		SpawnLocation* s = &spawns.at(i);
		if (!foundPlayer && s->type != PLAYER)
			continue;

		switch (s->type)
		{
			case PLAYER:
				if (foundPlayer)
					continue;

				mpUnits->addPlayer(s->x, s->y);
				foundPlayer = true;
				i = 0;
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

	assert(foundPlayer);
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