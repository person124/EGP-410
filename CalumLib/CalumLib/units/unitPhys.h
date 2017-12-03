#ifndef UNIT_PHYS_H
#define UNIT_PHYS_H

#include "physics/vector2.h"

#include "units/unit.h"

class UnitPhys : public Unit
{
	public:
		UnitPhys(const char* animString);
		~UnitPhys();

		void update(double dt);
		void draw();

		//Getters and Setters
		void setMaxSpeed(float speed) { mMaxSpeed = speed; };
		float getMaxSpeed() { return mMaxSpeed; };

		Vector2& getVelocity() { return mVel; };
		float getAngle() { return mAngle; };
		float getRotation() { return mRotation; };

		Vector2 getAngleAsVector();

		void setAngle(Vector2& vel);
		void setAngle(float angle) { mAngle = angle; };
		void setRotation(float angle) { mRotation = angle; };

		void setVelocity(Vector2& vel) { mVel = vel; };
		void setVelocity(float x, float y) { mVel.x = x; mVel.y = y; };

		//Misc Functions
		virtual void stop();
		bool checkForWalls(const Vector2& pos);
	protected:
		Vector2 mVel;
		float mAngle, mRotation;

		float mMaxSpeed;
};

#endif