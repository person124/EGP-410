#ifndef UNIT_SLOTTABLE_H
#define UNIT_SLOTTABLE_H

#include "UnitDynamic.h"

class UnitSlottable;
typedef WeightB(*SteeringFunc)(UnitSlottable* currentPos);

class UnitSlottable : public UnitDynamic
{
	public:
		UnitSlottable(SteeringFunc* behaviourArray, int size);
		virtual ~UnitSlottable();

		void update(float dt);
		
		SteeringOutput runBehaviours();
    private:
		SteeringFunc* mpBehaviourArray;
		int mBehaviourSize;
};

#endif