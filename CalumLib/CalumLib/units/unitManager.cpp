#include "UnitManager.h"

#include "globalConst.h"

#include "physics/vector2.h"

#include "units/unit.h"
#include "units/unitPlayer.h"
#include "units/unitSHA.h"
#include "units/unitCoin.h"
#include "units/unitCandy.h"

UnitManager::UnitManager()
{
	mpPlayer = NULL;
}

UnitManager::~UnitManager()
{
	removeAll();
	deleteLoop();

	if (mpPlayer != NULL)
		delete mpPlayer;
}

void UnitManager::addUnit(Unit* unit)
{
	mUnits.push_back(unit);
}

void UnitManager::removeUnit(unsigned int pos)
{
	if (pos < 0 || pos >= mUnits.size())
		return;
	mUnits.at(pos)->markForDeletion();
}

void UnitManager::removeUnit(Unit* unit)
{
	for (unsigned int i = 0; i < mUnits.size(); i++)
		if (mUnits.at(i) == unit)
		{
			mUnits.at(i)->markForDeletion();
			return;
		}
}

void UnitManager::removeAll()
{
	for each (Unit* unit in mUnits)
		unit->markForDeletion();
}

Unit* UnitManager::getUnit(unsigned int pos)
{
	return mUnits.at(pos);
}

Unit* UnitManager::getUnitAtPos(Vector2* pos)
{
	Unit* unit = NULL;

	for each (Unit* u in mUnits)
	{
		if (u->isPointInsideUnit(*pos))
		{
			unit = u;
			break;
		}
	}

	return unit;
}

int UnitManager::getSize()
{
	return mUnits.size();
}

void UnitManager::update(double dt)
{
	bool doDeletions = false;

	for each (Unit* unit in mUnits)
	{
		unit->update(dt);
		if (unit->shouldDelete())
			doDeletions = true;
	}

	if (doDeletions)
		deleteLoop();

	mpPlayer->update(dt);
}

void UnitManager::draw()
{
	for each (Unit* unit in mUnits)
		unit->draw();

	mpPlayer->draw();
}

void UnitManager::addPlayer(int x, int y)
{
	if (mpPlayer != NULL)
	{
		//TODO output error, player alreay exists
		return;
	}

	mpPlayer = new UnitPlayer(x * GC::TILE_SIZE, y * GC::TILE_SIZE);
}

void UnitManager::addSheerHeartAttack(int x, int y, int color)
{
	UnitSHA* sha = new UnitSHA((SHAColor) color);
	sha->setPosition(x * GC::TILE_SIZE, y * GC::TILE_SIZE);

	addUnit(sha);
}

void UnitManager::addCandy(int x, int y)
{
	UnitCandy* candy = new UnitCandy(x * GC::TILE_SIZE, y * GC::TILE_SIZE, mpPlayer);
	
	addUnit(candy);
}

void UnitManager::addCoin(int x, int y)
{
	UnitCoin* coin = new UnitCoin(x * GC::TILE_SIZE + 8, y * GC::TILE_SIZE + 8, mpPlayer);

	addUnit(coin);
}

void UnitManager::deleteLoop()
{
	bool repeat;

	do {
		repeat = false;

		for (unsigned int i = 0; i < mUnits.size(); i++)
		{
			if (mUnits.at(i)->shouldDelete())
			{
				repeat = true;
				deleteUnit(i);
				break;
			}
		}
	} while (repeat);
}

void UnitManager::deleteUnit(unsigned int pos)
{
	if (pos < 0 || pos >= mUnits.size())
		return;
	delete mUnits.at(pos);
	mUnits.erase(mUnits.begin() + pos);
}