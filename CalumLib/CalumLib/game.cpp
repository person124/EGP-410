#include "game.h"

#include "inputManager.h"
#include "globalConst.h"

#include "audio/audioSystem.h"

#include "events/eventSystem.h"
#include "events/eventSwitchState.h"
#include "events/eventLoadLevel.h"
#include "events/EventGameOver.h"

#include "gameMode/gameMode.h"
#include "gameMode/mainMenu.h"
#include "gameMode/editor.h"
#include "gameMode/level.h"
#include "gameMode/levelSelect.h"
#include "gameMode/gameOver.h"
#include "gameMode/help.h"

#include "graphics/graphicsSystem.h"
#include "graphics/graphicsBufferManager.h"
#include "graphics/animationManager.h"

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
	gpEventSystem->addListener(EVENT_GAME_OVER, this);
}

Game::~Game()
{
	destroy();
}

bool Game::initGame(int width, int height)
{
	mpGraphics = new GraphicsSystem(width, height);
	if (!mpGraphics->init())
		return false;

	mpBufferManager = new GraphicsBufferManager();
	mpAnimationManager = new AnimationManager();

	IOUtils::loadGraphicsBuffers(GC::PATH_GRAPHICS_BUFFERS);
	IOUtils::loadAnimations(GC::PATH_ANIMATIONS);

	mpAudio = new AudioSystem();
	if (!mpAudio->init())
		return false;

	IOUtils::loadAudio(GC::PATH_AUDIO);

	mpInputManager = new InputManager();
	if (!mpInputManager->init())
		return false;

	mFPS = 0.0f;

	mNextState = STATE_MAIN_MENU;
	switchState();

	srand(unsigned(time(NULL)));

	return true;
}

void Game::destroy()
{
	if (mpGraphics == NULL)
		return;

	delete mpBufferManager;
	delete mpAnimationManager;

	delete mpInputManager;

	if (mpGameMode != NULL)
		delete mpGameMode;

	//Audio is deleted last (almost) to make sure all clips have been cleared
	//first before deleted
	delete mpAudio;

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

void Game::update(const double& dt)
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
	else if (theEvent.getType() == EVENT_GAME_OVER)
	{
		const EventGameOver& e = static_cast<const EventGameOver&>(theEvent);

		mScore = e.getScore();

		mNextState = STATE_GAME_OVER;
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
		case STATE_HELP:
			mpGameMode = new Help();
			break;
		case STATE_SELECT_LEVEL:
			mpGameMode = new LevelSelect(GC::PATH_LEVELS);
			break;
		case STATE_EDITOR:
			mpGameMode = new Editor();
			break;
		case STATE_GAME_OVER:
			mpGameMode = new GameOver(mScore);
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