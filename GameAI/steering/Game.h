#pragma once

#include "PerformanceTracker.h"
#include "Defines.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <string>

#include "EventListener.h"

class GraphicsSystem;
class GraphicsBuffer;
class GraphicsBufferManager;
class SpriteManager;
class Timer;
class InputManager;
class UnitManager;
class HUD;

const IDType BACKGROUND_SPRITE_ID = 0;
const IDType PLAYER_ICON_SPRITE_ID = 1;
const IDType AI_ICON_SPRITE_ID = 2;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

class Game : public EventListener
{
public:
	Game();
	~Game();

	bool init();//returns true if no errors, false otherwise
	void cleanup();

	//game loop
	void beginLoop();
	void processLoop();
	bool endLoop();

	//Events
	void handleEvent(const Event& theEvent);

	inline GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };
	inline ALLEGRO_FONT* getFont() const { return mpFont; };
	inline InputManager* getInputManager() const { return mpInputManager; };
	inline UnitManager* getUnitManager() const { return mpUnitManager; };

	inline HUD* getHUD() const { return mpHUD; };

private:
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	bool mShouldExit;
	InputManager* mpInputManager;
	UnitManager* mpUnitManager;

	HUD* mpHUD;

	ALLEGRO_FONT* mpFont;
	ALLEGRO_SAMPLE* mpSample;
	IDType mBackgroundBufferID;
	IDType mPlayerIconBufferID;
	IDType mEnemyIconBufferID;
};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge

extern Game* gpGame;
extern PerformanceTracker* gpPerformanceTracker;