#include "game.h"

#include "inputManager.h"
#include "globalConst.h"

#include "audio/audioSystem.h"

#include "editor/editor.h"

#include "events/eventSystem.h"
#include "events/eventSwitchState.h"

#include "graphics/graphicsSystem.h"
#include "graphics/graphicsBufferManager.h"
#include "graphics/animationManager.h"

#include "gui/gui.h"
#include "gui/guiMainMenu.h"
#include "gui/guiEditor.h"

#include "pathing/grid.h"

#include "units/unitManager.h"

#include "utils/timer.h"
#include "utils/ioUtils.h"

#include <ctime>

Game* Game::pInstance = NULL;

void Game::init()
{
	if (pInstance == NULL)
		pInstance = new Game();
}

void Game::cleanup()
{
	if (pInstance != NULL)
		delete pInstance;
	pInstance = NULL;
}

Game::Game()
{
	mpGraphics = NULL;

	gpEventSystem->addListener(EVENT_QUIT, this);
	gpEventSystem->addListener(EVENT_SWITCH_STATE, this);
}

Game::~Game()
{
	destroy();
}

//TODO Move
#include "units/unitSHA.h"

bool Game::initGame(int width, int height)
{
	//TODO reorder
	mpGraphics = new GraphicsSystem(width, height);
	if (!mpGraphics->init())
		return false;

	mpAudio = new AudioSystem();
	if (!mpAudio->init())
		return false;

	mpInputManager = new InputManager();
	if (!mpInputManager->init())
		return false;

	mpBufferManager = new GraphicsBufferManager();
	mpAnimationManager = new AnimationManager();

	// Game assets
	IOUtils::loadGraphicsBuffers(PATH_GRAPHICS_BUFFERS);
	IOUtils::loadAnimations(PATH_ANIMATIONS);
	IOUtils::loadAudio(PATH_AUDIO);

	mFPS = 0.0f;

	mpGrid = NULL;

	mNextState = STATE_COUNT;
	handleEvent(EventSwitchState(STATE_MAIN_MENU));

	mpUnitManager = new UnitManager();
	mpUnitManager->addUnit(new UnitSHA(yellow));

	mpEditor = NULL;

	return true;
}

void Game::destroy()
{
	//TODO reorder
	if (mpGraphics == NULL)
		return;

	delete mpInputManager;

	delete mpBufferManager;
	delete mpAnimationManager;

	if (mpGrid != NULL)
		delete mpGrid;

	delete mpGUI;

	delete mpAudio;

	delete mpUnitManager;

	if (mpEditor != NULL)
		delete mpEditor;

	mpGraphics->destroy();
	delete mpGraphics;
	mpGraphics = NULL;
}

void Game::mainLoop()
{
	Timer* updateTimer = new Timer();
	Timer* FPSTimer = new Timer();
	mRunning = true;

	updateTimer->start();
	while (mRunning)
	{
		FPSTimer->start();

		double uTime = updateTimer->getElapsedTime();
		update(uTime);
		updateTimer->start();

		draw();

		FPSTimer->sleepUntilElapsed(FPS);
		FPSTimer->stop();
		mFPS = FPSTimer->getElapsedTime() * UPStoFPS;
	}

	updateTimer->stop();

	delete updateTimer;
	delete FPSTimer;
}

void Game::update(float dt)
{
	mpInputManager->update();

	if (mNextState != STATE_COUNT)
		switchState();

	if (mCurrentState == STATE_EDITOR)
	{
		mpEditor->update(dt);
	}
	else
	{
		mpUnitManager->update(dt);

		mpGUI->update(dt);
	}
}

void Game::draw()
{
	mpGraphics->clear();

	if (mCurrentState == STATE_IN_GAME)
	{
		mpGrid->draw();

		mpUnitManager->draw();
	}
	else if (mCurrentState == STATE_EDITOR)
		mpEditor->draw();

	mpGUI->draw();

	mpGraphics->flip();
}

GraphicsSystem* Game::getGraphics()
{
	return mpGraphics;
}

AudioSystem* Game::getAudio()
{
	return mpAudio;
}

void Game::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_QUIT)
		mRunning = false;
	else if (theEvent.getType() == EVENT_SWITCH_STATE)
	{
		const EventSwitchState& e = static_cast<const EventSwitchState&>(theEvent);
		mNextState = e.getState();
		/*
		switch (e.getState())
		{
			case STATE_MAIN_MENU:
				if (mpGUI != NULL)
					mToDelete = mpGUI;
				mpGUI = new GUIMainMenu();

				if (mpEditor != NULL)
					mDeleteEditor = true;

				mCurrentState = e.getState();
				break;
			case STATE_EDITOR:
				if (mpGUI != NULL)
					mToDelete = mpGUI;
				mpGUI = new GUIEditor();

				mCurrentState = e.getState();
				break;
			default:
				break;
		}
		*/
	}
}

GraphicsBufferManager* Game::getBufferManager()
{
	return mpBufferManager;
}

AnimationManager* Game::getAnimationManager()
{
	return mpAnimationManager;
}

UnitManager* Game::getUnits()
{
	return mpUnitManager;
}

void Game::switchState()
{
	switch (mNextState)
	{
		case STATE_MAIN_MENU:
			if (mpGUI != NULL)
				delete mpGUI;
			mpGUI = new GUIMainMenu();

			if (mpEditor != NULL)
			{
				delete mpEditor;
				mpEditor = NULL;
			}

			break;
		case STATE_EDITOR:
			if (mpGUI != NULL)
				delete mpGUI;
			mpGUI = new GUIEditor();

			mpEditor = new Editor((GUIEditor*)mpGUI);

			break;
		default:
			return;
	}

	mCurrentState = mNextState;
	mNextState = STATE_COUNT;
}