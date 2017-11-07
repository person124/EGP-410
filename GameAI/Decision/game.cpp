#include "game.h"
#include "ioUtils.h"

#include "inputManager.h"
#include "globalConst.h"

#include "events/eventSystem.h"
#include "events/eventQuit.h"

#include "graphics/graphicsSystem.h"
#include "graphics/graphicsBufferManager.h"
#include "graphics/animationManager.h"
#include "graphics/font.h"

#include "pathing/grid.h"

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
	gpEventSystem->addListener(EVENT_SAVE, this);
	gpEventSystem->addListener(EVENT_LOAD, this);
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

	mpInputManager = new InputManager();
	if (!mpInputManager->init())
	{
		initError("input system");
		return false;
	}

	mpBufferManager = new GraphicsBufferManager();
	mpAnimationManager = new AnimationManager();

	// Game assets
	IOUtils::loadGraphicsBuffers(PATH_GRAPHICS_BUFFERS);
	IOUtils::loadAnimations(PATH_ANIMATIONS);
	mpFont = new Font(40, PATH_FONT);

	mFPS = 0.0f;

	GraphicsBuffer* bg = new GraphicsBuffer(800, 600, Color(0, 0, 0));
	mpBufferManager->add("background", bg);

	mpGrid = new Grid();

	return true;
}

void Game::destroy()
{
	if (mpGraphics == NULL)
		return;

	delete mpInputManager;

	delete mpBufferManager;
	delete mpAnimationManager;
	delete mpFont;

	delete mpGrid;

	mpGraphics->destroy();
	delete mpGraphics;
	mpGraphics = NULL;

	gpEventSystem->removeListenerFromAllEvents(this);
}

void Game::mainLoop()
{
	PerformanceTracker* pTracker = new PerformanceTracker();
	Timer* pTimer = new Timer();
	mRunning = true;

	pTracker->startTracking("UpdateTime");
	while (mRunning)
	{
		pTimer->start();

		double uTime = pTracker->getElapsedTime("UpdateTime");
		update(uTime);
		//cout << "Update Time: " << uTime << '\n';
		pTracker->clearTracker("UpdateTime");

		draw();

		pTimer->sleepUntilElapsed(FPS);
		pTimer->stop();
		mFPS = pTimer->getElapsedTime() * UPStoFPS;
	}

	pTracker->stopTracking("UpdateTime");

	delete pTracker;
	delete pTimer;
}

void Game::update(float dt)
{
	mpInputManager->update();
}

void Game::draw()
{
	mpGraphics->draw(0, 0, mpBufferManager->get("background"));

	mpGrid->draw();

	mpGraphics->flip();
}

GraphicsSystem* Game::getGraphics()
{
	return mpGraphics;
}

void Game::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_QUIT)
	{
		mRunning = false;
	}
	else if (theEvent.getType() == EVENT_SAVE)
		IOUtils::saveGrid(PATH_GRID_SAVE, mpGrid);
	else if (theEvent.getType() == EVENT_LOAD)
		IOUtils::loadGrid(PATH_GRID_SAVE, mpGrid);
}

GraphicsBufferManager* Game::getBufferManager()
{
	return mpBufferManager;
}

AnimationManager* Game::getAnimationManager()
{
	return mpAnimationManager;
}

Font* Game::getFont()
{
	return mpFont;
}