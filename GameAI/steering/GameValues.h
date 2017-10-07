#ifndef GAME_VALUES_H
#define GAME_VALUES_H

#include "EventListener.h"

#include "GameValueTypes.h"

class GameValues : public EventListener
{
	public:
		GameValues();
		~GameValues();

		float getValue(int pos);
		std::string getValueString(int pos);
		int getCurrentSelected() { return mCurrentModValue; };

		void handleEvent(const Event& theEvent);
	private:
		int mCurrentModValue = -1;
		float mValues[MOD_NUM_TYPES];
};

#endif