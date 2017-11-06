#ifndef GAME_H
#define GAME_H

#include "events/eventListener.h"

#include <PerformanceTracker.h>
#include <Trackable.h>

class GraphicsSystem;
class InputManager;
class GraphicsBufferManager;
class AnimationManager;
class HUD;
class Grid;

class Game : public EventListener
{
	public:
		static Game* pInstance;
		static void init();
		static void cleanup();
	
		Game();
		~Game();
		bool initGame(int width, int height);
		void destroy();
		void mainLoop();
		GraphicsSystem* getGraphics();
		void handleEvent(const Event& theEvent);
	
		const double FPS = 1000.0 / 60.0;
		const double UPStoFPS = 3600.0 / 1000.0;
	
		GraphicsBufferManager* getBufferManager();
		AnimationManager* getAnimationManager();
	
	private:
		void update(float dt);
		void draw();

		bool mRunning;
	
		GraphicsSystem* mpGraphics;
		InputManager* mpInputManager;
		GraphicsBufferManager* mpBufferManager;
		AnimationManager* mpAnimationManager;
		HUD* mpHud;
		Grid* mpGrid;
	
		//Things to do with the actuall game:
		float mFPS;
};

#endif