#include "level.h"

#include "globalConst.h"

#include "pathing/grid.h"

#include "units/unitManager.h"

#include "utils/ioUtils.h"

#include <string>

Level::Level(const char* levelName)
{
	std::string path = PATH_LEVELS;
	path += '/';
	path += levelName;

	IOUtils::loadGrid(path, mpGrid);

	mpUnits = new UnitManager();

	createGraph();
	initSpawns();
	populateCoins();
}

Level::~Level()
{
	delete mpUnits;
}

void Level::update(double dt)
{
	mpUnits->update(dt);
}

void Level::draw()
{
	mpGrid->draw();

	mpUnits->draw();
}

void Level::createGraph()
{
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
				break;
		}
	}
}

void Level::populateCoins()
{
}