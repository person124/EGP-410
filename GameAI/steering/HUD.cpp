#include "HUD.h"

#include "EventSystem.h"
#include "EventMouseMove.h"

#include <sstream>

#include "Game.h"

HUD::HUD()
{
	gpEventSystem->addListener(EVENT_MOUSE_MOVE, this);
}

HUD::~HUD()
{
}

void HUD::draw()
{
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), mX, mY, ALLEGRO_ALIGN_CENTER, mStrMousePos.c_str());
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
}