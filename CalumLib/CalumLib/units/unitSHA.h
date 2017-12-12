#ifndef UNIT_SHA_H
#define UNIT_SHA_H

#include "events/eventListener.h"

#include "units/unitPhys.h"

enum SHAColor
{
	blue,
	red,
	yellow,
	SHA_COLOR_COUNT
};

class StateTreeSHA;
class MovementSHA;
class UnitPlayer;

class UnitSHA : public UnitPhys, public EventListener
{
	public:
		UnitSHA(float x, float y, SHAColor color, Unit* player);
		~UnitSHA();

		void update(double dt);
		void draw();

		void handleEvent(const Event& theEvent);

		int getCurrentState();

		void setTargetLocation(Vector2 pos) { mTarget = pos; };
		Vector2 getTargetLocation() { return mTarget; };
		Vector2 getSpawnLocation() { return mSpawn; };
	private:
		Vector2 mSpawn;
		Vector2 mTarget;

		Animation* mpAniBase;
		Animation* mpAniFear;
		Animation* mpAniEnraged;
		Animation* mpAniRespawn;
		Animation* mpAniORA;

		StateTreeSHA* mpStateTree;

		MovementSHA* mpMovement;

		UnitPlayer* mpPlayerRef;
};

#endif