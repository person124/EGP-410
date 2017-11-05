#ifndef UNIT_H
#define UNIT_H

#include "../graphics/animation.h"

#include <string>

#include <Trackable.h>

//TODO Redo unit
class Unit : public Trackable
{
    public:
        Unit(Animation* animation, int x = 0, int y = 0);
		Unit(const std::string& animationKey, int x = 0, int y = 0);
		virtual ~Unit();

		//Update and Draw
        virtual void update(double dt);
        virtual void draw();

		void setLocation(int x, int y);
		int getX();
		int getY();
		Animation*& getAnimation();
		bool isInside(int x, int y);

		//== operator
		bool operator==(Unit& unit);
    protected:
        int mX, mY;
        Animation* mpAnimation;
};

#endif