#include "UnitManager.h"

#include "Unit.h"
#include "UnitPlayer.h"
#include "UnitDynamic.h"

#include "EventSystem.h"
#include "EventAddAI.h"
#include "EventDeleteAI.h"

#include "Game.h"
#include "SpriteManager.h"

UnitManager::UnitManager()
{
	mpPlayer = new UnitPlayer();

	gpEventSystem->addListener(EVENT_ADD_AI, this);
	gpEventSystem->addListener(EVENT_DELETE_AI, this);
}

UnitManager::~UnitManager()
{
	removeAll();
	delete mpPlayer;
	mpPlayer = NULL;
}

void UnitManager::addUnit(Unit*& unit)
{
	mUnits.push_back(unit);
}

void UnitManager::removeUnit(unsigned int pos)
{
	if (pos < 0 || pos >= mUnits.size())
		return;
	delete mUnits.at(pos);
	mUnits.erase(mUnits.begin() + pos);
}

void UnitManager::removeUnit(Unit*& unit)
{
	for (unsigned int i = 0; i < mUnits.size(); i++)
		if (mUnits.at(i) == unit)
		{
			removeUnit(i);
			return;
		}
}

void UnitManager::removeAll()
{
	for each (Unit* unit in mUnits)
		delete unit;
	mUnits.clear();
}

Unit*& UnitManager::getUnit(unsigned int pos)
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

	mpPlayer->update(dt);
}

void UnitManager::draw(GraphicsBuffer* buffer)
{
	for each (Unit* unit in mUnits)
		unit->draw(buffer);

	mpPlayer->draw(buffer);
}

void UnitManager::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_ADD_AI)
	{
		const EventAddAI& e = static_cast<const EventAddAI&>(theEvent);
		Unit* unit = new UnitDynamic(gpGame->getSpriteManager()->getSprite(2), e.isArrive());
		unit->setPosition(mpPlayer->getX() + 200, mpPlayer->getY());
		addUnit(unit);
	}
}

Vector2& UnitManager::getRandDistFromPlayer(float distance)
{
	Vector2 output;

	//TODO

	return output;
}