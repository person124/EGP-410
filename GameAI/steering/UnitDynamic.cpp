#include "UnitDynamic.h"

#include "Game.h"
#include "UnitManager.h"
#include "UnitPlayer.h"
#include "GraphicsSystem.h"

UnitDynamic::UnitDynamic(bool isArrive):Unit(AI_ICON_SPRITE_ID)
{
	//mSteer.linear = { 0, 0 };
	mSteer.angular = 0.0f;

	mArrive = isArrive;

	setMaxAccel(100);
	setMaxSpeed(150);

    setTargetRadius(10);
    setSlowRadius(100);
    setTimeToTarget(0.5);
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

	if (mVel.length() > mMaxSpeed) 
	{
		mVel.normalize();
		mVel *= mMaxSpeed;
	}

	GRAPHICS_SYSTEM->wrapCoordinates(mPos);

    setAngle(mVel);
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
    Vector2 direction = target - mPos;
    float distance = direction.length();

    if (distance < mTargetRadius)
    {
        stop();
        return;
    }

    float targetSpeed;
    if (distance > mSlowRadius)
        targetSpeed = mMaxSpeed;
    else
        targetSpeed = (mMaxSpeed * distance) / mSlowRadius;

    Vector2 targetVelocity = direction;
    targetVelocity.normalize();
    targetVelocity *= targetSpeed;

    mSteer.linear = targetVelocity - mVel;
    mSteer.linear /= mTimeToTarget;

    if (mSteer.linear.length() > mMaxAccel)
    {
        mSteer.linear.normalize();
        mSteer.linear *= mMaxAccel;
    }
}