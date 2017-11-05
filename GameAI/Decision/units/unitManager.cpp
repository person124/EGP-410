#include "unitManager.h"

#include "unit.h"

UnitManager::UnitManager()
{
}

UnitManager::~UnitManager()
{
	removeAll();
}

void UnitManager::addUnit(Unit* unit)
{
	mUnits.push_back(unit);
}

void UnitManager::removeUnit(Unit* unit)
{
	for (unsigned int i = 0; i < mUnits.size(); i++)
	{
		if (*mUnits.at(i) == *unit) {
			removeUnit(i);
			return;
		}
	}
}

void UnitManager::removeUnit(unsigned int pos)
{
	if (pos < 0 || pos >= mUnits.size())
		return;
	delete mUnits.at(pos);
	mUnits.erase(mUnits.begin() + pos);
}

void UnitManager::removeAll()
{
	for each (Unit* unit in mUnits)
		delete unit;
	mUnits.clear();
}

Unit* UnitManager::getUnit(unsigned int pos)
{
	return mUnits.at(pos);
}

int UnitManager::getSize()
{
	return mUnits.size();
}

void UnitManager::update(float dt)
{
	for each (Unit* unit in mUnits)
		unit->update(dt);
}

void UnitManager::draw()
{
	for each (Unit* unit in mUnits)
		unit->draw();
}