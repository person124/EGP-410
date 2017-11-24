#include "editor.h"

#include "game.h"
#include "globalConst.h"

#include "events/eventSystem.h"
#include "events/eventClick.h"
#include "events/eventKeypress.h"
#include "events/eventSwitchState.h"

#include "graphics/animationManager.h"
#include "graphics/graphicsSystem.h"

#include "gui/guiEditor.h"

#include "pathing/grid.h"

#include "utils/timer.h"
#include "utils/ioUtils.h"

Editor::Editor()
{
	GUIEditor* gui = new GUIEditor();

	mpGUI = gui;
	mpGEdit = gui;

	mpGraphics = Game::pInstance->getGraphics();

	mpGrid = new Grid(30, 30);

	gpEventSystem->addListener(EVENT_KEYPRESS, this);
	gpEventSystem->addListener(EVENT_CLICK, this);

	mCurrentType = TILE;
	for (int i = 0; i < EDITOR_SELECTIONS_COUNT; i++)
		mCurrent[i] = 0;
	
	//Gets the number of tiles
	Animation* ani = Game::pInstance->getAnimationManager()->get("tiles");
	mMax[0] = ani->getLength();
	delete ani;

	//Total number of different spawns (0 player, 1-3 baddies, 4 candy)
	ani = Game::pInstance->getAnimationManager()->get("editor_spawns");
	mMax[1] = ani->getLength();
	delete ani;

	mDrawSolid = false;

	mpTimer = new Timer();

	mpGEdit->changeSelected(mCurrentType);
}

Editor::~Editor()
{
	gpEventSystem->removeListenerFromAllEvents(this);

	delete mpTimer;
}

void Editor::update(double dt)
{
	if (mpTimer->getElapsedTime() > 2)
	{
		mpTimer->stop();
		mpGEdit->renderSaveMessage(false);
		mpGEdit->renderLoadMessage(false);
	}
}

void Editor::draw()
{
	if (!mDrawSolid)
		mpGrid->draw();
	else
		mpGrid->drawSolidity();
	mpGrid->drawSpawnLocations();

	mpGUI->draw();
}

void Editor::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_KEYPRESS)
	{
		const EventKeypress& e = static_cast<const EventKeypress&>(theEvent);

		switch (e.getKey())
		{
			case KEYS_CONFIRM:
				gpEventSystem->fireEvent(EventSwitchState(STATE_MAIN_MENU));
				return;

			case KEYS_SAVE_MAP:
				IOUtils::saveGrid(PATH_EDITOR_SAVE, mpGrid);
				mpGEdit->renderSaveMessage(true);

				if (mpTimer->getElapsedTime() > 0)
					mpGEdit->renderLoadMessage(false);
				mpTimer->start();

				return;
			case KEYS_LOAD_MAP:
				IOUtils::loadGrid(PATH_EDITOR_SAVE, mpGrid);
				mpGEdit->renderLoadMessage(true);

				if (mpTimer->getElapsedTime() > 0)
					mpGEdit->renderSaveMessage(false);
				mpTimer->start();

				return;

			case KEYS_TOGGLE_SOLIDITY:
				mDrawSolid = !mDrawSolid;
				return;

			//Keys to move camera
			case KEYS_CAMERA_UP:
				mpGraphics->offsetOffset(0, -15);
				return;
			case KEYS_CAMERA_DOWN:
				mpGraphics->offsetOffset(0, 15);
				return;
			case KEYS_CAMERA_LEFT:
				mpGraphics->offsetOffset(-15, 0);
				return;
			case KEYS_CAMERA_RIGHT:
				mpGraphics->offsetOffset(15, 0);
				return;

			//Keys to change currently selected
			case KEYS_DOWN:
				mCurrentType--;
				break;
			case KEYS_UP:
				mCurrentType++;
				break;
			case KEYS_LEFT:
				mCurrent[mCurrentType]--;
				break;
			case KEYS_RIGHT:
				mCurrent[mCurrentType]++;
				break;

			default:
				break;
		}

		if (mCurrent[mCurrentType] < 0)
			mCurrent[mCurrentType] = mMax[mCurrentType] - 1;
		else if (mCurrent[mCurrentType] >= mMax[mCurrentType])
			mCurrent[mCurrentType] = 0;

		mpGEdit->changeSelected(mCurrentType);

		mpGEdit->setTileFrame(mCurrent[TILE]);
		mpGEdit->setSpawnFrame(mCurrent[SPAWNS]);
	}
	else if (theEvent.getType() == EVENT_CLICK)
	{
		const EventClick& e = static_cast<const EventClick&>(theEvent);

		//Place a tile / spawn at click
		int tileX = (e.getX() + mpGraphics->getXOffset()) / TILE_SIZE;
		int tileY = (e.getY() + mpGraphics->getYOffset()) / TILE_SIZE;

		if (mCurrentType == TILE)
			mpGrid->setID(tileX, tileY, mCurrent[TILE]);
		else if (mCurrentType == SPAWNS)
		{
			if (e.getButton() == left_mouse_button)
				mpGrid->addSpawnLocation((SpawnType)mCurrent[SPAWNS], tileX, tileY);
			else
				mpGrid->removeSpawnLocation(tileX, tileY);
		}
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