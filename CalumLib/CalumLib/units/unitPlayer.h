#ifndef UNIT_PLAYER_H
#define UNIT_PLAYER_H

#include "events/eventListener.h"

#include "units/unitPhys.h"

class Timer;
class AudioClip;

class UnitPlayer : public UnitPhys, public EventListener
{
	public:
		UnitPlayer(int x, int y);
		~UnitPlayer();

		void update(double dt);
		void draw();

		void handleEvent(const Event& theEvent);

		bool isInvincible() { return mCandyStage > 0; };
	private:
		Timer* mpTimer;
		AudioClip* mpORA;
		Animation* mpAniORA;

		int mCandyStage;
};

#endif