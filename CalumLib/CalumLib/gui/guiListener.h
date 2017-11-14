#ifndef GUI_LISTENER_H
#define GUI_LISTENER_H

#include "events/eventListener.h"

#include "gui/gui.h"

class GUIListener : public GUI, public EventListener
{
	public:
		GUIListener();
		~GUIListener();

		virtual void registerEvents();
		virtual void removeEvents();

		void handleEvent(const Event& theEvent);
};

#endif