#include "HUD.h"

#include "EventSystem.h"
#include "EventMouseMove.h"

#include <sstream>

#include "Game.h"
#include "GameValues.h"

HUD::HUD()
{
	gpEventSystem->addListener(EVENT_MOUSE_MOVE, this);

	gpEventSystem->addListener(EVENT_TOGGLE_DEBUG, this);
}

HUD::~HUD()
{
}

void HUD::draw()
{
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), mX, mY, ALLEGRO_ALIGN_CENTER, mStrMousePos.c_str());

	if (mDrawDebug)
	{
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "Enemy (V)elocity:");
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), 0, 25, ALLEGRO_ALIGN_LEFT, "Reaction (R)adius:");
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), 0, 50, ALLEGRO_ALIGN_LEFT, "(A)ngular Velocity:");
	}
}

void HUD::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_MOUSE_MOVE)
	{
		const EventMouseMove& e = static_cast<const EventMouseMove&>(theEvent);

		mX = e.getX();
		mY = e.getY();

		std::stringstream ss;
		ss << mX << ":" << mY;
		mStrMousePos = ss.str();
	}
	else if (theEvent.getType() == EVENT_TOGGLE_DEBUG)
	{
		mDrawDebug = !mDrawDebug;
	}
}