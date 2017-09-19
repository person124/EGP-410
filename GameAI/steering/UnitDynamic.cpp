#include "UnitDynamic.h"

#include "Game.h"
#include "UnitManager.h"
#include "UnitPlayer.h"
#include "GraphicsSystem.h"

#include <iostream>

UnitDynamic::UnitDynamic(Sprite* sprite, bool isArrive):Unit(sprite)
{
	//mSteer.linear = { 0, 0 };
	mSteer.angular = 0.0f;

	mArrive = isArrive;

	setMaxAccel(100);
	setMaxSpeed(300);
}

UnitDynamic::~UnitDynamic()
{
}

void UnitDynamic::update(float dt)
{
	//Get target
	if (mArrive)
		arrive(gpGame->getUnitManager()->getPlayer()->getPosition());
	else 
		seek(gpGame->getUnitManager()->getPlayer()->getPosition());

	mPos += mVel * dt + 0.5f * mSteer.linear * (dt * dt);
	mAngle += mRotation * dt + 0.5f * mSteer.angular * (dt * dt);

	mVel += mSteer.linear * dt;
	mRotation += mSteer.angular * dt;

	if (mVel.length() > mMaxSpeed) 
	{
		mVel.normalize();
		mVel *= mMaxSpeed;
	}

	GRAPHICS_SYSTEM->wrapCoordinates(mPos);
}

void UnitDynamic::seek(Vector2& target)
{
	mSteer.linear = target - mPos;
	mSteer.linear.normalize();
	mSteer.linear *= mMaxAccel;

	mSteer.angular = 0;
}

void UnitDynamic::arrive(Vector2& target)
{

}