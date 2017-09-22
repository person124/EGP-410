#ifndef UNIT_H
#define UNIT_H

#include "Phys.h"

#include <Trackable.h>

class Sprite;
class GraphicsBuffer;

class Unit : public Trackable
{
	public:
		Unit(int spriteID);
		~Unit();
		virtual void update(float dt);
		void draw(GraphicsBuffer* buffer);

        virtual void stop();

		// Getters and Setters
		void setMaxSpeed(float speed) { mMaxSpeed = speed; };
		float getMaxSpeed() { return mMaxSpeed; };

		void setPosition(Vector2& pos) { mPos = pos; };
		void setPosition(float x, float y) { mPos.x = x; mPos.y = y; };
		Vector2& getPosition() { return mPos; };
		float getX() { return mPos.x; };
		float getY() { return mPos.y; };

		void setAngle(Vector2& vel);
	protected:
		Sprite* mpSprite;
		Vector2 mPos, mVel;
		SteeringOutput mSteer;
		float mAngle, mRotation;
		
		float mMaxSpeed;
};

#endif