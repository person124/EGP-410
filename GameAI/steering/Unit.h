// MadeByCalum
#ifndef UNIT_H
#define UNIT_H

#include <Trackable.h>

class Sprite;
class GraphicsBuffer;

struct Vector2
{
	int x, y;
};

class Unit : public Trackable
{
	public:
		Unit();
		~Unit();
		void update(float dt);
		void draw(GraphicsBuffer* buffer);
	private:
		Sprite* mpSprite;
		Vector2 mPos, mVel;
		float mAngle, mRotation;
};

#endif