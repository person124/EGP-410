#include "GUI.h"

#include "EventSystem.h"
#include "EventMouseMove.h"
#include "EventToggleDebug.h"
#include "EventHelp.h"

#include "GameValueTypes.h"

#include "Game.h"
#include "GameValues.h"
#include "GraphicsSystem.h"

#include <allegro5\allegro_primitives.h>

const int HELP_NUM = 13;
const std::string HELP_TEXT[HELP_NUM] = {
	"         Escape:                       Closes the Game",
	"              F:                            Add a Unit",
	"              I:              Spawn 5 Units in Cluster",
	"              D: Delete a Random Unit/Mouseovered Unit",
	"            TAB:                       Clear All Units",
	"              O:                       Open Debug Menu",
	"<Specified Key>:                Select Value to Change",
	"              +:               Increase Selected Value",
	"              -:               Decrease Selected Value",
	"       SPACEBAR:                      Pause Simulation",
	"              ?:                 Change GUI/Wall Color",
	"              Z:                  Reset GUI/Wall Color",
	"              ~:                      Toggle this Text"
};

GUI::GUI()
{
	gpEventSystem->addListener(EVENT_MOUSE_MOVE, this);

	gpEventSystem->addListener(EVENT_TOGGLE_DEBUG, this);

	gpEventSystem->addListener(EVENT_TOGGLE_HELP, this);

	mVal = gpGame->getValues();
}

GUI::~GUI()
{
}

void GUI::draw()
{
	GRAPHICS_SYSTEM->drawText(mX, mY, mStrMousePos);
	al_draw_filled_circle(mX, mY, 2, al_map_rgb(0, 0, 0));

	if (mDrawDebug)
	{
		for (int i = 0; i < MOD_NUM_TYPES; i++)
		{
			char c = '-';
			if (mVal->getCurrentSelected() == i)
				c = '>';
			GRAPHICS_SYSTEM->drawText(0, 20 * i, c + MOD_GUI_STRING[i] + mVal->getValueString(i), ALLEGRO_ALIGN_LEFT);
		}
	}

	if (mDrawHelp)
	{
		for (int i = 0; i < HELP_NUM; i++)
		{
			GRAPHICS_SYSTEM->drawText(GRAPHICS_SYSTEM->getWidth(), 20 * i, HELP_TEXT[i], ALLEGRO_ALIGN_RIGHT);
		}
	}
}

void GUI::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_MOUSE_MOVE)
	{
		const EventMouseMove& e = static_cast<const EventMouseMove&>(theEvent);

		mX = e.getX();
		mY = e.getY();

		mStrMousePos = std::to_string(mX) + ":" + std::to_string(mY);
	}
	else if (theEvent.getType() == EVENT_TOGGLE_DEBUG)
	{
		mDrawDebug = !mDrawDebug;
	}
	else if (theEvent.getType() == EVENT_TOGGLE_HELP)
	{
		mDrawHelp = !mDrawHelp;
	}
}