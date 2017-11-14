#ifndef GUI_H
#define GUI_H

#include "utils/trackable.h"

class GUIElement;

class GUI : public Trackable
{
	public:
		GUI();
		~GUI();

		void draw();
	private:
		int mElementCount;
		GUIElement** mpElements;
};

#endif