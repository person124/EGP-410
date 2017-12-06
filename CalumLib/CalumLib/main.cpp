#include "game.h"

#include "globalConst.h"

#include "events/eventSystem.h"

#include "utils/memoryTracker.h"

#include <iostream>
#include <stdlib.h>
#include <ctime>

int main()
{
	gpEventSystem = new EventSystem();
	Game::init();

	if (Game::pInstance->initGame(GC::WINDOW_WIDTH, GC::WINDOW_HEIGHT))
	{
		//TODO Move this to inside Game
		srand(unsigned(time(NULL)));
		Game::pInstance->mainLoop();
	}

	Game::cleanup();

	delete gpEventSystem;

	gMemoryTracker.reportPointers(std::cout);

	return 0;
}