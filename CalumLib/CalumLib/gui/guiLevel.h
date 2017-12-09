#ifndef GUI_LEVEL_H
#define GUI_LEVEL_H

#include "events/eventListener.h"

#include "gui/gui.h"

class Animation;

class GUILevel : public GUI, public EventListener
{
	public:
		GUILevel();
		~GUILevel();

		void update(double dt);
		void draw();

		void setScore(int s);

		void handleEvent(const Event& theEvent);
	private:
		Animation* mpOraSpawn;
		bool mRenderSpawn;
		int mOraX, mOraY;
};

#endif