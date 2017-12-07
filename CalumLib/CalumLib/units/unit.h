#ifndef UNIT_H
#define UNIT_H

#include "physics/vector2.h"

#include "utils/trackable.h"

class Animation;

class Unit : public Trackable
{
	public:
		Unit(const char* animString);
		virtual ~Unit();

		//Drawing and movement
		virtual void update(double dt);
		virtual void draw();
	
		// Getters and Setters
		bool shouldDelete() { return mShouldDelete; };
		void markForDeletion() { mShouldDelete = true; };

		void setPosition(Vector2& pos) { mPos = pos; };
		void setPosition(float x, float y) { mPos.x = x; mPos.y = y; };
		void setPosition(int x, int y) { mPos.x = (float)x; mPos.y = (float)y; };

		Vector2& getPosition() { return mPos; };
		float getX() { return mPos.x; };
		float getY() { return mPos.y; };
	
		//Misc Functions
		bool isPointInsideUnit(Vector2& point);
		bool isUnitTouching(Unit* otherUnit);
	protected:
		bool mShouldDelete;

		Animation* mpAnim;
		float mAniScale;

		Vector2 mPos;
};

#endif