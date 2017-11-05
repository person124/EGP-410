#include "game.h"

#include "events/eventSystem.h"

#include <iostream>

#include <MemoryTracker.h>

int main()
{
	const int WIDTH = 800, HEIGHT = 600;

	gpEventSystem = new EventSystem();
	Game::init();

	if (Game::pInstance->initGame(WIDTH, HEIGHT))
	{
		Game::pInstance->mainLoop();
	}

	Game::cleanup();

	delete gpEventSystem;

	gMemoryTracker.reportAllocations(std::cout);
	system("pause");

	return 0;
}