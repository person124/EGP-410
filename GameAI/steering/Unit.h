#ifndef UNIT_H
#define UNIT_H

#include "Phys.h"

#include <Trackable.h>

class Sprite;
class GraphicsBuffer;

class Unit : public Trackable
{
	public:
		Unit(Sprite* sprite);
		~Unit();
		void update(float dt);
		void draw(GraphicsBuffer* buffer);

		// Getters and Setters
		void setMaxSpeed(float speed) { mMaxSpeed = speed; };
		float getMaxSpeed() { return mMaxSpeed; };

		void setAngle(Vector2& vel);
	protected:
		Sprite* mpSprite;
		Vector2 mPos, mVel;
		SteeringOutput mSteer;
		float mAngle, mRotation;
		
		float mMaxSpeed;
};

#endif