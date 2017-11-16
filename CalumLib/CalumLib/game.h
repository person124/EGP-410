#ifndef GAME_H
#define GAME_H

#include "events/eventListener.h"

#include "utils/trackable.h"

//TODO Reorder
class GraphicsSystem;
class InputManager;
class GraphicsBufferManager;
class AnimationManager;
class AudioSystem;
class Grid;
class GUI;
class UnitManager;

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
		AudioSystem* getAudio();
		void handleEvent(const Event& theEvent);
	
		GraphicsBufferManager* getBufferManager();
		AnimationManager* getAnimationManager();
		UnitManager* getUnits();
	private:
		void update(float dt);
		void draw();

		bool mRunning;
	
		//TODO Reorder
		GraphicsSystem* mpGraphics;
		InputManager* mpInputManager;
		GraphicsBufferManager* mpBufferManager;
		AnimationManager* mpAnimationManager;
		AudioSystem* mpAudio;
		Grid* mpGrid;
		GUI* mpGUI;
		UnitManager* mpUnitManager;
	
		float mFPS;
};

#endif