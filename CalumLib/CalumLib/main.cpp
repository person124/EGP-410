#include "game.h"

#include "events/eventSystem.h"

#include <iostream>

#include "utils/memoryTracker.h"

int main()
{
	const int WIDTH = 800, HEIGHT = 800;

	gpEventSystem = new EventSystem();
	Game::init();

	if (Game::pInstance->initGame(WIDTH, HEIGHT))
	{
		Game::pInstance->mainLoop();
	}

	Game::cleanup();

	delete gpEventSystem;

	gMemoryTracker.reportPointers(std::cout);

	return 0;
}