#include "game.h"

#include "ioUtils.h"
#include "inputManager.h"
#include "globalConst.h"

#include "audio/audioSystem.h"

#include "events/eventSystem.h"

#include "graphics/graphicsSystem.h"
#include "graphics/graphicsBufferManager.h"
#include "graphics/animationManager.h"

#include "gui/gui.h"

#include "pathing/grid.h"

#include "units/unitManager.h"

#include "utils/timer.h"

#include <ctime>

enum GameState
{
	MAIN_MENU,
	IN_GAME,
	OPTIONS,
	EDITOR
};

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
}

Game::~Game()
{
	destroy();
}

//TODO Move
#include "gui/guiMainMenu.h"
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

	mpGrid = new Grid();

	mCurrentState = MAIN_MENU;
	mpGUI = new GUIMainMenu();

	mpUnitManager = new UnitManager();
	mpUnitManager->addUnit(new UnitSHA(yellow));

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

	delete mpGrid;

	delete mpGUI;

	delete mpAudio;

	delete mpUnitManager;

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

	mpUnitManager->update(dt);

	mpGUI->update(dt);
}

void Game::draw()
{
	mpGraphics->clear();

	mpGrid->draw();

	mpUnitManager->draw();

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
	{
		mRunning = false;
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