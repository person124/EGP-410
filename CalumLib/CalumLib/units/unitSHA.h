#ifndef UNIT_SHA_H
#define UNIT_SHA_H

#include "units/unitPhys.h"

enum SHAColor
{
	blue,
	red,
	yellow,
	SHA_COLOR_COUNT
};

class StateTreeSHA;
struct MovementSHA;

class UnitSHA : public UnitPhys
{
	public:
		UnitSHA(SHAColor color);
		~UnitSHA();

		void update(double dt);
		void draw();

		int getCurrentState();

		void setTargetLocation(Vector2 pos) { mTarget = pos; };
		Vector2 getTargetLocation() { return mTarget; };
	private:
		Vector2 mTarget;

		Animation* mpAniBase;
		Animation* mpAniFear;
		Animation* mpAniEnraged;
		Animation* mpAniRespawn;

		StateTreeSHA* mpStateTree;

		MovementSHA* mpMovement;
};

#endif