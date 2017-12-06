#include "guiSelectable.h"

#include "globalConst.h"

#include "events/eventSystem.h"
#include "events/eventKeypress.h"

#include "gui/elements/guiText.h"

#include <assert.h>

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
	for (int i = 0; i < mSize; i++)
		delete mpEvents[i];
	delete[] mpEvents;

	delete mpSelectorText;

	gpEventSystem->removeListener(EVENT_KEYPRESS, this);
}

void GUISelectable::draw()
{
	GUI::draw();
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
				if (mCurrent != -1)
					gpEventSystem->fireEvent(*mpEvents[mCurrent]);
				return;
			default:
				break;
		}

		if (mCurrent < 0)
			mCurrent = mSize - 1;
		else if (mCurrent >= mSize)
			mCurrent = 0;

		refreshSelector();
	}
}

void GUISelectable::refreshSelector()
{
	GUIElement* ele = mpElements[mpSelections[mCurrent]];
	mpSelectorText->setX(ele->getX() - GC::FONT_SIZE);
	mpSelectorText->setY(ele->getY());
}

void GUISelectable::setSelectableCount(int count)
{
	mSize = count;
	mpSelections = new int[mSize];

	mpEvents = new Event*[mSize];
	for (int i = 0; i < mSize; i++)
		mpEvents[i] = NULL;
}

void GUISelectable::addSelectable(int pos, Event* theEvent)
{
	int slot;
	for (slot = 0; slot < mSize; slot++)
		if (mpEvents[slot] == NULL)
			break;

	assert(slot < mSize);

	mpSelections[slot] = pos;
	mpEvents[slot] = theEvent;
}