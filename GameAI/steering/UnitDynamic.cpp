// MadeByCalum
#include "UnitDynamic.h"

UnitDynamic::UnitDynamic(Sprite* sprite, bool isArrive):Unit(sprite)
{
	//mSteer.linear = { 0, 0 };
	mSteer.angular = 0.0f;

	mArrive = isArrive;
}

UnitDynamic::~UnitDynamic()
{
}

void UnitDynamic::update(float dt)
{
	mPos += mVel * dt + 0.5f * mSteer.linear * (dt * dt);
	mAngle += mRotation * dt + 0.5f * mSteer.angular * (dt * dt);

	mVel += mSteer.linear * dt;
	mRotation += mSteer.angular * dt;
}

void UnitDynamic::seek(Vector2& target)
{

}

void UnitDynamic::arrive(Vector2& target)
{

}