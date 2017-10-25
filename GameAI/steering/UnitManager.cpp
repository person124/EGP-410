#include "UnitManager.h"

#include "Game.h"
#include "WallManager.h"

#include "Unit.h"
#include "UnitPlayer.h"
#include "UnitSlottable.h"

#include "EventSystem.h"
#include "EventAddAI.h"
#include "EventDeleteAI.h"
#include "EventClearAI.h"
#include "EventQuit.h"

#include "Game.h"
#include "SpriteManager.h"

#include "MovementFunctions.h"

// For random
#define _USE_MATH_DEFINES
#include <math.h>

const float RAND_ANGLE = static_cast<float>(RAND_MAX / (2 * M_PI));

UnitManager::UnitManager()
{
	mpPlayer = new UnitPlayer();

	gpEventSystem->addListener(EVENT_ADD_AI, this);
	gpEventSystem->addListener(EVENT_DELETE_AI, this);
	gpEventSystem->addListener(EVENT_CLEAR_AI, this);

    srand(unsigned(time(NULL)));
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
		/*
		const EventAddAI& e = static_cast<const EventAddAI&>(theEvent);

		int size = 4;
		SteeringFunc* funcs = new SteeringFunc[size];
		funcs[0] = e.isFlee() ? mfFlee : mfSeek;
		funcs[1] = mfWander;
		funcs[2] = mfAvoid;
		funcs[3] = mfWallAvoid;

		Unit* unit = new UnitSlottable(funcs, size, e.isFlee() ? AI_FLEE_SPRITE_ID : AI_SEEK_SPRITE_ID);

        //For position, its 100 if it is flee, and 200 if seek
        unit->setPosition(getRandDistFromPlayer(e.isFlee() ? 100 : 200));

		addUnit(unit);
		*/
	}
    else if (theEvent.getType() == EVENT_DELETE_AI)
    {
        if (getSize() == 0)
        {
            gpEventSystem->fireEvent(EventQuit());
            return;
        }

        int random = rand() % getSize();
        removeUnit(random);
    }
	else if (theEvent.getType() == EVENT_CLEAR_AI)
	{
		removeAll();
	}
}

Vector2 UnitManager::getRandDistFromPlayer(float distance)
{
	Vector2 output;
	do {
		output = mpPlayer->getPosition();

		float angle = rand() / (RAND_ANGLE);

		output.x += distance * cos(angle);
		output.y += distance * sin(angle);
	} while (gpGame->getWallManager()->isInsideWall(output));

	return output;
}

float UnitManager::randomBinomial()
{
	return ((float)rand() / RAND_MAX) - ((float)rand() / RAND_MAX);
}