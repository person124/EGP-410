#ifndef UNIT_H
#define UNIT_H

#include "physics/vector2.h"

#include "utils/trackable.h"

class Animation;
struct SteeringOutput;

class Unit : public Trackable
{
	public:
		Unit(const char* animString);
		virtual ~Unit();

		//Drawing and movement
		virtual void update(double dt);
		virtual void draw();
	
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
	
		//Misc Functions
		virtual void stop();
		bool isPointInsideUnit(Vector2& point);
	protected:
		Animation* mpAnim;
		Vector2 mPos, mVel;
		SteeringOutput* mSteer;
		float mAngle, mRotation;
	
		float mMaxSpeed;
};

#endif