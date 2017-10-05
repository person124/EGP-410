#ifndef HUD_H
#define HUD_H

#include "EventListener.h"

#include <string>

class HUD : public EventListener
{
	public:
		HUD();
		~HUD();

		//void update(float dt);
		void draw();

		void handleEvent(const Event& theEvent);
	private:
		std::string mStrMousePos;
		int mX, mY;

		bool mDrawDebug = false;
};

#endif