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
class GameMode;
class Grid;

enum GameState;

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

		GameMode* getCurrentMode();
		Grid* getCurrentGrid();
	private:
		void update(float dt);
		void draw();

		void switchState();

		bool mRunning;
	
		//TODO Reorder
		GraphicsSystem* mpGraphics;
		InputManager* mpInputManager;
		GraphicsBufferManager* mpBufferManager;
		AnimationManager* mpAnimationManager;
		AudioSystem* mpAudio;
		GameMode* mpGameMode;
	
		float mFPS;
		GameState mCurrentState, mNextState;
		const char* mLevelToLoad;
};

#endif