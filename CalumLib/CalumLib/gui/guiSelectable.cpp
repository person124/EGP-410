#include "guiSelectable.h"

#include "globalConst.h"

#include "events/eventSystem.h"
#include "events/eventKeypress.h"

#include "gui/elements/guiText.h"

GUISelectable::GUISelectable()
{
	registerEvents();

	mCurrent = 0;
	mSize = 0;
	mpSelections = NULL;
	mpEvents = NULL;

	mpSelectorText = new GUIText(0, 0, ">");
}

GUISelectable::~GUISelectable()
{
	delete[] mpSelections;
	delete[] mpEvents;

	delete mpSelectorText;
}

void GUISelectable::draw()
{
	mpSelectorText->draw();
}

void GUISelectable::registerEvents()
{
	gpEventSystem->addListener(EVENT_KEYPRESS, this);
}

void GUISelectable::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_KEYPRESS)
	{
		const EventKeypress& e = static_cast<const EventKeypress&>(theEvent);

		switch (e.getKey())
		{
			case KEYS_UP:
				mCurrent--;
				break;
			case KEYS_DOWN:
				mCurrent++;
				break;
			case KEYS_CONFIRM:
				gpEventSystem->fireEvent(mpEvents[mCurrent]);
				break;
			default:
				break;
		}

		if (mCurrent < 0)
			mCurrent = mSize - 1;
		else if (mCurrent >= mSize)
			mCurrent = 0;

		GUIElement* ele = mpElements[mpSelections[mCurrent]];
		mpSelectorText->setX(ele->getX() - FONT_SIZE);
		mpSelectorText->setY(ele->getY());
	}
}