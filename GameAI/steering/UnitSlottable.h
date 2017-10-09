#ifndef UNIT_SLOTTABLE_H
#define UNIT_SLOTTABLE_H

#include "Unit.h"

class UnitSlottable;
typedef WeightB(*SteeringFunc)(UnitSlottable* currentPos);

class UnitSlottable : public Unit
{
	public:
		UnitSlottable(SteeringFunc* behaviourArray, int size, int spriteMod);
		virtual ~UnitSlottable();

		void update(float dt);
		
		SteeringOutput runBehaviours();
    private:
		SteeringFunc* mpBehaviourArray;
		int mBehaviourSize;

		void checkWall(Vector2& old, Vector2& pos);
};

#endif