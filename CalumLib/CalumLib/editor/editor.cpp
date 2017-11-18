#include "editor.h"

#include "events/eventSystem.h"
#include "events/eventClick.h"
#include "events/eventKeypress.h"

#include "pathing/grid.h"

Editor::Editor()
{
	mpGrid = new Grid(30, 30);

	gpEventSystem->addListener(EVENT_KEYPRESS, this);
	gpEventSystem->addListener(EVENT_CLICK, this);

	mCurrentType = TILE;
	for (int i = 0; i < EDITOR_SELECTIONS_COUNT; i++)
		mCurrent[i] = 0;
	
	mMax[0] = 2; //Number of tiles
	mMax[1] = 5; //Number of different spawns (1 player, 3 baddies, candy)
}

Editor::~Editor()
{
	gpEventSystem->removeListenerFromAllEvents(this);
	delete mpGrid;
}

void Editor::update(double dt)
{
}

void Editor::draw()
{
	mpGrid->draw();
}

void Editor::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_KEYPRESS)
	{
		const EventKeypress& e = static_cast<const EventKeypress&>(theEvent);

		if (e.getKey() == KEYS_DOWN)
			mCurrentType--;
		else if (e.getKey() == KEYS_UP)
			mCurrentType++;
		else if (e.getKey() == KEYS_LEFT)
			mCurrent[mCurrentType]--;
		else if (e.getKey() == KEYS_RIGHT)
			mCurrent[mCurrentType]++;
	}
	else if (theEvent.getType() == EVENT_CLICK)
	{
		const EventClick& e = static_cast<const EventClick&>(theEvent);

		//Place a tile / spawn at click
	}
}

EditorSelections operator++(EditorSelections& sel, int)
{
	int temp = sel;
	temp++;

	if (temp >= EDITOR_SELECTIONS_COUNT)
		temp = 0;

	sel = (EditorSelections) temp;

	return sel;
}

EditorSelections operator--(EditorSelections& sel, int)
{
	int temp = sel;
	temp--;

	if (temp < 0)
		temp = EDITOR_SELECTIONS_COUNT - 1;

	sel = (EditorSelections)temp;

	return sel;
}

/*
	Press left and right to change tile
	Up and down to change type
	Starts off as a massive grid that is trimmed down when save?
	Enter to save
	Types are:
		-Tiles
		-Spawns
*/