#include "game.h"

#include "inputManager.h"
#include "globalConst.h"

#include "audio/audioSystem.h"

#include "events/eventSystem.h"
#include "events/eventSwitchState.h"
#include "events/eventLoadLevel.h"

#include "graphics/graphicsSystem.h"
#include "graphics/graphicsBufferManager.h"
#include "graphics/animationManager.h"

#include "gameMode/gameMode.h"
#include "gameMode/mainMenu.h"
#include "gameMode/editor.h"
#include "gameMode/level.h"
#include "gameMode/levelSelect.h"
#include "gameMode/gameOver.h"

#include "utils/timer.h"
#include "utils/ioUtils.h"

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
	gpEventSystem->addListener(EVENT_LOAD_LEVEL, this);
}

Game::~Game()
{
	destroy();
}

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
	IOUtils::loadGraphicsBuffers(GC::PATH_GRAPHICS_BUFFERS);
	IOUtils::loadAnimations(GC::PATH_ANIMATIONS);
	IOUtils::loadAudio(GC::PATH_AUDIO);

	mFPS = 0.0f;

	mNextState = STATE_MAIN_MENU;
	switchState();

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

	delete mpAudio;

	if (mpGameMode != NULL)
		delete mpGameMode;

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

		FPSTimer->sleepUntilElapsed(GC::FPS);
		FPSTimer->stop();
		mFPS = FPSTimer->getElapsedTime() * GC::UPStoFPS;
	}

	updateTimer->stop();

	delete updateTimer;
	delete FPSTimer;
}

void Game::update(float dt)
{
	mpInputManager->update();

	mpGameMode->update(dt);

	if (mNextState != STATE_COUNT)
		switchState();
}

void Game::draw()
{
	mpGraphics->clear();

	mpGameMode->draw();

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
	}
	else if (theEvent.getType() == EVENT_LOAD_LEVEL)
	{
		const EventLoadLevel& e = static_cast<const EventLoadLevel&>(theEvent);

		mNextState = STATE_IN_GAME;
		e.getLevelName(mLevelToLoad);
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

GameMode* Game::getCurrentMode()
{
	return mpGameMode;
}

Grid* Game::getCurrentGrid()
{
	if (mpGameMode == NULL)
		return NULL;
	return mpGameMode->getGrid();
}

void Game::switchState()
{
	if (mpGameMode != NULL && mNextState != STATE_IN_GAME)
		delete mpGameMode;

	switch (mNextState)
	{
		default:
		case STATE_MAIN_MENU:
			mpGameMode = new MainMenu();
			break;
		case STATE_SELECT_LEVEL:
			mpGameMode = new LevelSelect(GC::PATH_LEVELS);
			break;
		case STATE_EDITOR:
			mpGameMode = new Editor();
			break;
		case STATE_GAME_OVER:
			mpGameMode = new GameOver();
			break;
		case STATE_IN_GAME:
			GameMode* old = mpGameMode;

			mpGameMode = new Level(mLevelToLoad);

			delete old;
			break;
	}

	mCurrentState = mNextState;
	mNextState = STATE_COUNT;
}