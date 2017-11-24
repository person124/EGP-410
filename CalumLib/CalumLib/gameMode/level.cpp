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