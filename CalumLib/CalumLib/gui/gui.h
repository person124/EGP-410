#ifndef GUI_H
#define GUI_H

#include "utils/trackable.h"

class GUIElement;

class GUI : public Trackable
{
	public:
		GUI();
		virtual ~GUI();

		virtual void update(double dt);
		virtual void draw();
	protected:
		int mElementCount;
		GUIElement** mpElements;
};

#endif