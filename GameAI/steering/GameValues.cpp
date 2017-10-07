#include "GameValues.h"

#include "EventSystem.h"
#include "EventModify.h"
#include "EventModifyStat.h"

GameValues::GameValues()
{
	gpEventSystem->addListener(EVENT_MODIFY, this);
	gpEventSystem->addListener(EVENT_MODIFY_STAT, this);

	//TODO be able to set adjustment amounts
	//TODO add min and maxs
	mValues[MOD_VELOCITY] = 10.0f;
	mValues[MOD_REACTION_RADIUS] = 300.0f;
	mValues[MOD_ANGULAR_SPEED] = 10.0f;
}

GameValues::~GameValues()
{
}

float GameValues::getValue(int pos)
{
	if (pos <= MOD_INVALID || pos >= MOD_NUM_TYPES)
		return 0.0f;

	return mValues[pos];
}

std::string GameValues::getValueString(int pos)
{
	return std::to_string(getValue(pos));
}

void GameValues::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_MODIFY)
	{
		const EventModify& e = static_cast<const EventModify&>(theEvent);

		if (mCurrentModValue == -1)
			return;

		if (e.isIncrease())
			mValues[mCurrentModValue] += 0.5f;
		else
			mValues[mCurrentModValue] -= 0.5f;
	}
	else if (theEvent.getType() == EVENT_MODIFY_STAT)
	{
		const EventModifyStat& e = static_cast<const EventModifyStat&>(theEvent);

		if (e.getValue() != MOD_INVALID || e.getValue() != MOD_NUM_TYPES)
			mCurrentModValue = e.getValue();
	}
}