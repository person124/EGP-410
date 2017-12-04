#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "events/eventListener.h"

#include "gameMode/gameMode.h"

class AudioClip;
class Timer;
class Animation;
class Color;

class GameOver : public GameMode, public EventListener
{
	public:
		GameOver();
		~GameOver();

		void update(double dt);
		void draw();

		void handleEvent(const Event& theEvent);
	private:
		AudioClip* mpAudio;
		Timer* mpTimer;

		Animation* mpPlayer;

		Color* mpColor;
		int mWMid, mHMid;

		bool mAnimationDone;
};

#endif