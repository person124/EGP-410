#ifndef UNIT_PHYS_H
#define UNIT_PHYS_H

#include "physics/vector2.h"

#include "units/unit.h"

struct SteeringOutput;

class UnitPhys : public Unit
{
	public:
		UnitPhys(const char* animString);
		~UnitPhys();

		void update(double dt);

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

		//Misc Functions
		virtual void stop();
	private:
		Vector2 mVel;
		SteeringOutput* mpSteer;
		float mAngle, mRotation;

		float mMaxSpeed;
};

#endif