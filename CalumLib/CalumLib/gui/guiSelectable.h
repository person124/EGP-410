#ifndef GUI_SELECTABLE_H
#define GUI_SELECTABLE_H

#include "gui/guiListener.h"

class GUIText;

class GUISelectable : public GUIListener
{
	public:
		GUISelectable();
		~GUISelectable();

		void draw();

		void registerEvents();

		void handleEvent(const Event& theEvent);

		void refreshSelector();
	protected:
		void setMax(int max);
		void addSelectable(int pos, Event* theEvent);
	private:
		int mCurrent, mSize;
		int* mpSelections;
		Event** mpEvents;

		GUIText* mpSelectorText;
};

#endif