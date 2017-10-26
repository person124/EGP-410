#include "GameValues.h"

#include "Game.h"

#include "EventSystem.h"
#include "EventModify.h"
#include "EventModifyStat.h"

#include <cmath>
#include <fstream>

float GameValues::value(int pos)
{
	return gpGame->getValues()->getValue(pos);
}

GameValues::GameValues()
{
	gpEventSystem->addListener(EVENT_MODIFY, this);
	gpEventSystem->addListener(EVENT_MODIFY_STAT, this);

	gpEventSystem->addListener(EVENT_SAVE, this);
	gpEventSystem->addListener(EVENT_LOAD, this);

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

void GameValues::saveValues()
{
	std::ofstream ofile = std::ofstream("GameValues.dat");

	if (!ofile.is_open())
	{
		printf("Error with opening file: GameValues.dat!!!!!\n");
		return;
	}

	for (int i = 0; i < MOD_NUM_TYPES; i++)
	{
		ofile << value(i);
		if (i + 1 < MOD_NUM_TYPES)
			ofile << '\n';
	}

	ofile.close();
}

void GameValues::loadValues()
{
	std::ifstream ifile = std::ifstream("GameValues.dat");

	if (!ifile.is_open())
	{
		printf("Error with opening file: GameValues.dat!!!!!\n");
		return;
	}

	float v;
	std::string junk;
	for (int i = 0; i < MOD_NUM_TYPES; i++)
	{
		ifile >> v;
		MOD_VALUES[i].check(v);
		mValues[i] = v;
		getline(ifile, junk);
	}

	ifile.close();
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

		float temp = mValues[mCurrentModValue];
		temp = std::roundf(temp * 100.0f) / 100.0f;
		mValues[mCurrentModValue] = temp;
	}
	else if (theEvent.getType() == EVENT_MODIFY_STAT)
	{
		const EventModifyStat& e = static_cast<const EventModifyStat&>(theEvent);

		if (e.getValue() != MOD_INVALID || e.getValue() != MOD_NUM_TYPES)
			mCurrentModValue = e.getValue();
	}
	else if (theEvent.getType() == EVENT_SAVE)
		saveValues();
	else if (theEvent.getType() == EVENT_LOAD)
		loadValues();
}