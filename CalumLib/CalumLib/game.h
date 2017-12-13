#ifndef GAME_H
#define GAME_H

#include "events/eventListener.h"

#include "utils/trackable.h"

class GraphicsSystem;
class GraphicsBufferManager;
class AnimationManager;
class AudioSystem;
class InputManager;
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
		void update(const double& dt);
		void draw();

		void switchState();

		bool mRunning;
	
		GraphicsSystem* mpGraphics;
		GraphicsBufferManager* mpBufferManager;
		AnimationManager* mpAnimationManager;
		AudioSystem* mpAudio;
		InputManager* mpInputManager;
		GameMode* mpGameMode;
	
		float mFPS;
		GameState mCurrentState, mNextState;
		const char* mLevelToLoad;
		int mScore;
};

#endif