#include "GameValues.h"

#include "Game.h"

#include "EventSystem.h"
#include "EventModify.h"
#include "EventModifyStat.h"

float GameValues::value(int pos)
{
	return gpGame->getValues()->getValue(pos);
}

GameValues::GameValues()
{
	gpEventSystem->addListener(EVENT_MODIFY, this);
	gpEventSystem->addListener(EVENT_MODIFY_STAT, this);

	for (int i = 0; i < MOD_NUM_TYPES; i++)
		mValues[i] = MOD_VALUES[i].starting;
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
			mValues[mCurrentModValue] += MOD_VALUES[mCurrentModValue].adjust;
		else
			mValues[mCurrentModValue] -= MOD_VALUES[mCurrentModValue].adjust;

		MOD_VALUES[mCurrentModValue].check(mValues[mCurrentModValue]);
	}
	else if (theEvent.getType() == EVENT_MODIFY_STAT)
	{
		const EventModifyStat& e = static_cast<const EventModifyStat&>(theEvent);

		if (e.getValue() != MOD_INVALID || e.getValue() != MOD_NUM_TYPES)
			mCurrentModValue = e.getValue();
	}
}