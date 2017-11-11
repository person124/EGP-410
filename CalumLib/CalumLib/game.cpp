#include "game.h"

#include "ioUtils.h"
#include "inputManager.h"
#include "globalConst.h"

#include "audio/audioSystem.h"

#include "utils/timer.h"

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
	mpFont = new Font(FONT_SIZE, PATH_FONT);
	IOUtils::loadAudio(PATH_AUDIO);

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
	mpAudio->get("temp")->play(false);
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