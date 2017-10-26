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
		virtual ~Unit();
		virtual void update(float dt);
		virtual void draw(GraphicsBuffer* buffer);

        virtual void stop();

		// Getters and Setters
		void setMaxSpeed(float speed) { mMaxSpeed = speed; };
		float getMaxSpeed() { return mMaxSpeed; };

		void setPosition(Vector2& pos) { mPos = pos; };
		void setPosition(float x, float y) { mPos.x = x; mPos.y = y; };
		Vector2& getPosition() { return mPos; };
		float getX() { return mPos.x; };
		float getY() { return mPos.y; };
		Vector2& getVelocity() { return mVel; };
		float getAngle() { return mAngle; };
		float getRotation() { return mRotation; };

		Vector2 getAngleAsVector();

		void setAngle(Vector2& vel);
		void setAngle(float angle) { mAngle = angle; };
		void setRotation(float angle) { mRotation = angle; };
	protected:
		Sprite* mpSprite;
		Vector2 mPos, mVel;
		SteeringOutput mSteer;
		float mAngle, mRotation;
		
		float mMaxSpeed;
};

#endif