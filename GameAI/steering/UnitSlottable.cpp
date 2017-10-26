#include "UnitSlottable.h"

#include <allegro5\allegro_primitives.h>

#include "Game.h"
#include "GameValues.h"
#include "UnitManager.h"
#include "WallManager.h"
#include "GraphicsSystem.h"

UnitSlottable::UnitSlottable(SteeringFunc* behaviourArray, int size, int sprite):Unit(sprite)
{
	mpBehaviourArray = behaviourArray;
	mBehaviourSize = size;
}

UnitSlottable::~UnitSlottable()
{
}

void UnitSlottable::update(float dt)
{
	mMaxSpeed = GameValues::value(MOD_SPEED);

	mSteer = runBehaviours();

	//Vector2 pOld = mPos;

	mPos += mVel * dt + 0.5f * mSteer.linear * (dt * dt);
	mAngle += mRotation * dt + 0.5f * mSteer.angular * (dt * dt);

	mVel += mSteer.linear * dt;
	mRotation += mSteer.angular * dt;

	//checkWall(pOld, mPos);

	if (mVel.length() > mMaxSpeed)
	{
		mVel.normalize();
		mVel *= mMaxSpeed;
	}

	GRAPHICS_SYSTEM->wrapCoordinates(mPos);

	//setAngle(mVel);
}

void UnitSlottable::draw(GraphicsBuffer* buffer)
{
	Unit::draw(buffer);

	if (GameValues::value(MOD_DISPLAY_TIPS) == 1)
	{
		Vector2 end = mPos;
		end += mVel.normal() * 150;
		al_draw_line(mPos.x, mPos.y, end.x, end.y, al_map_rgb(0, 0, 0), 2);

		Vector2 ang = mPos;
		ang += getAngleAsVector() * 150;
		al_draw_line(mPos.x, mPos.y, ang.x, ang.y, al_map_rgb(238, 232, 170), 2);

		float delta = 0.05f;
		float a = mVel.toAngle();
		al_draw_arc(mPos.x, mPos.y, 150, a - delta, 2 * delta, al_map_rgb(0, 0, 255), 2);

		float wanderOffset = GameValues::value(MOD_WANDER_OFFSET);
		float wanderRadius = GameValues::value(MOD_WANDER_RADIUS);

		Vector2 circlePos = getPosition();
		circlePos += wanderOffset * getAngleAsVector();
		al_draw_circle(circlePos.x, circlePos.y, wanderRadius, al_map_rgb(255, 255, 255), 2);
	}
}

SteeringOutput UnitSlottable::runBehaviours()
{
	SteeringOutput output;

	for (int i = 0; i < mBehaviourSize; i++)
	{
		WeightB behav = mpBehaviourArray[i](this);
		output.linear += behav.weight * behav.steering.linear;
		output.angular += behav.weight * behav.steering.angular;
	}

	return output;
}

void UnitSlottable::checkWall(Vector2& old, Vector2& pos)
{
	if (gpGame->getWallManager()->isInsideWall(pos))
		pos = old;
}