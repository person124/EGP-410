#include "UnitManager.h"

#include "Game.h"
#include "GameValues.h"
#include "WallManager.h"

#include "Unit.h"
#include "UnitSlottable.h"

#include "EventSystem.h"
#include "EventAddAI.h"
#include "EventDeleteAI.h"
#include "EventClearAI.h"
#include "EventQuit.h"
#include "EventMouseMove.h"

#include "Game.h"
#include "SpriteManager.h"

#include "MovementFunctions.h"

// For random
#define _USE_MATH_DEFINES
#include <math.h>

const float RAND_ANGLE = static_cast<float>(RAND_MAX / (2 * M_PI));

UnitManager::UnitManager()
{
	gpEventSystem->addListener(EVENT_ADD_AI, this);
	gpEventSystem->addListener(EVENT_DELETE_AI, this);
	gpEventSystem->addListener(EVENT_CLEAR_AI, this);

	gpEventSystem->addListener(EVENT_MOUSE_MOVE, this);

    srand(unsigned(time(NULL)));

	std::vector<SteeringFunc> funcs;
	funcs.push_back(slot::wallAvoid);
	funcs.push_back(slot::wander);
	funcs.push_back(slot::face);
	funcs.push_back(slot::seperation);
	funcs.push_back(slot::cohesion);
	funcs.push_back(slot::matchVelocity);
	funcs.push_back(slot::avoid);

	mFuncCount = funcs.size();
	mfFuncs = new SteeringFunc[mFuncCount];
	for (int i = 0; i < mFuncCount; i++)
		mfFuncs[i] = funcs.at(i);
}

UnitManager::~UnitManager()
{
	removeAll();
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

Unit*& UnitManager::getUnitAtPos(Vector2& pos)
{
	Unit* unit = NULL;

	for each (Unit* u in mUnits)
	{
		if (u->isPointInsideUnit(pos))
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

void UnitManager::update(float dt)
{
	for each (Unit* unit in mUnits)
		unit->update(dt);
}

void UnitManager::draw(GraphicsBuffer* buffer)
{
	for each (Unit* unit in mUnits)
		unit->draw(buffer);
}

void UnitManager::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_ADD_AI)
	{
		const EventAddAI& e = static_cast<const EventAddAI&>(theEvent);

		Unit* unit = new UnitSlottable(mfFuncs, mFuncCount, AI_FLEE_SPRITE_ID);

		float angle = rand() / RAND_ANGLE;

		unit->setPosition(mMouseX, mMouseY);
		unit->setAngle(angle);

		addUnit(unit);

		if (e.spawnCluster())
		{
			Vector2 pos = unit->getPosition();
			float dist = GameValues::value(MOD_SPREAD);

			for (int i = 0; i < 4; i++)
			{
				unit = new UnitSlottable(mfFuncs, mFuncCount, AI_FLEE_SPRITE_ID);

				unit->setPosition(offsetPosition(pos, dist));
				unit->setAngle(angle);

				addUnit(unit);
			}
		}
	}
    else if (theEvent.getType() == EVENT_DELETE_AI)
    {
        if (getSize() == 0)
        {
            gpEventSystem->fireEvent(EventQuit());
            return;
        }

		Unit* unit = getUnitAtPos(Vector2(mMouseX, mMouseY));
		if (unit != NULL)
		{
			removeUnit(unit);
			return;
		}

        int random = rand() % getSize();
        removeUnit(random);
    }
	else if (theEvent.getType() == EVENT_CLEAR_AI)
	{
		removeAll();
	}
	else if (theEvent.getType() == EVENT_MOUSE_MOVE)
	{
		const EventMouseMove& e = static_cast<const EventMouseMove&>(theEvent);

		mMouseX = e.getX();
		mMouseY = e.getY();
	}
}

Vector2 UnitManager::offsetPosition(Vector2& base, float distance)
{
	float angle = rand() / RAND_ANGLE;

	Vector2 output = base;
	output.x += cos(angle) * distance;
	output.y += sin(angle) * distance;

	return output;
}

float UnitManager::randomBinomial()
{
	return ((float)rand() / RAND_MAX) - ((float)rand() / RAND_MAX);
}