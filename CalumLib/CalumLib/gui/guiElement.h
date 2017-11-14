#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include "utils/trackable.h"

class GUIElement : public Trackable
{
	public:
		GUIElement() {};
		virtual ~GUIElement() {};

		virtual void update(double dt) {};
		virtual void draw() {};

		void setX(int x) { mX = x; };
		void setY(int y) { mY = y; };

		int getX() { return mX; };
		int getY() { return mY; };
	protected:
		int mX, mY;
};

#endif