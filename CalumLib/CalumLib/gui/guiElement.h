#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include "utils/trackable.h"

class GUIElement : public Trackable
{
	public:
		GUIElement() {};
		virtual ~GUIElement() {};

		virtual void draw() {};
};

#endif