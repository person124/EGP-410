#ifndef GUI_H
#define GUI_H

#include "EventListener.h"
#include "GameValueTypes.h"

class GameValues;

class GUI : public EventListener
{
	public:
		GUI();
		~GUI();

		//void update(float dt);
		void draw();

		void handleEvent(const Event& theEvent);
	private:
		std::string mStrMousePos;
		int mX, mY;

		bool mDrawDebug = false;
		GameValues* mVal;
};

#endif