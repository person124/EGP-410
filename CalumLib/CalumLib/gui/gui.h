#ifndef GUI_H
#define GUI_H

#include "utils/trackable.h"

class GUIElement;

class GUI : public Trackable
{
	public:
		GUI();
		virtual ~GUI();

		virtual void update(const double& dt);
		virtual void draw();
	protected:
		void setElementCount(int count);

		int mElementCount;
		GUIElement** mpElements;
};

#endif