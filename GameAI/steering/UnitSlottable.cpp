#include "UnitSlottable.h"

UnitSlottable::UnitSlottable(SteeringFunc* behaviourArray, int size):UnitDynamic(true)
{
	mpBehaviourArray = behaviourArray;
	mBehaviourSize = size;

	/*
	setMaxSpeed(300);
	*/
}

UnitSlottable::~UnitSlottable()
{
	delete[] mpBehaviourArray;
}

void UnitSlottable::update(float dt)
{
	mSteer = runBehaviours();

	UnitDynamic::update(dt);
}

SteeringOutput UnitSlottable::runBehaviours()
{
	SteeringOutput output;

	for (int i = 0; i < mBehaviourSize; i++)
	{
		WeightB behav = mpBehaviourArray[i]();
		output.linear += behav.weight * behav.steering.linear;
	}

	return output;
}