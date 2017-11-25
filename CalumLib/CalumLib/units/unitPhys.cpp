#include "unitPhys.h"

#include "physics/steeringOutput.h"

#include <cmath>

UnitPhys::UnitPhys(const char* animString) : Unit(animString)
{
	mVel = Vector2();

	mpSteer = new SteeringOutput();
}

UnitPhys::~UnitPhys()
{
	delete mpSteer;
}

void UnitPhys::update(double dt)
{
	Unit::update(dt);

	float t = (float)dt;
	mPos += mVel * t + 0.5f * mpSteer->linear * (t * t);
	mAngle += mRotation * t + 0.5f * mpSteer->angular * (t * t);

	mVel += mpSteer->linear * t;
	mRotation += mpSteer->angular * t;
}

Vector2 UnitPhys::getAngleAsVector()
{
	return Vector2::toVector(mAngle);
}

void UnitPhys::setAngle(Vector2& vel)
{
	if (vel.length() != 0)
		mAngle = atan2f(vel.y, vel.x);
}

void UnitPhys::stop()
{
	mVel = Vector2(0, 0);
	mRotation = 0;

	mpSteer->linear = Vector2(0, 0);
	mpSteer->angular = 0;
}