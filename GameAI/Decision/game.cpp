#include "game.h"
#include "ioUtils.h"

#include "events/eventSystem.h"
#include "events/eventQuit.h"

#include "graphics/graphicsSystem.h"
#include "graphics/graphicsBufferManager.h"
#include "graphics/animationManager.h"
#include "graphics/hud.h"

#include "pathing/grid.h"

#include "inputManager.h"

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

	mpHud = new Hud();

	// Game assets
	IOUtils::loadGraphicsBuffers("assets/graphics_buffers.dat");
	IOUtils::loadAnimations("assets/animations.dat");

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

	//TODO reorganize
	delete mpBufferManager;
	delete mpAnimationManager;

	delete mpHud;

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
	//TODO
	//mpHud->update(mLives, mScore, mFPS);

	mpInputManager->update();
}

void Game::draw()
{
	mpGraphics->draw(0, 0, mpBufferManager->get("background"));

	mpGrid->draw();

	mpHud->drawFPS();

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
}

GraphicsBufferManager* Game::getBufferManager()
{
	return mpBufferManager;
}

AnimationManager* Game::getAnimationManager()
{
	return mpAnimationManager;
}