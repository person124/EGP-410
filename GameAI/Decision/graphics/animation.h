#ifndef ANIMATION_H
#define ANIMATION_H

#include "graphics/sprite.h"

#include <vector>

#include <Trackable.h>

class Animation : public Trackable
{
	public:
		//Constructors
		Animation(std::vector<Sprite>* sprites, double time, bool loop = true);
		Animation(double time, bool loop = true);
		Animation(Animation* ani);
		~Animation();

		//Misc.
		void addSprite(Sprite& sprite);
		void update(double dt);

		//Setters
		void setSpeed(double newSpeed);
		void setFrame(int frame);

		//Getters
		double getSpeed();
		Sprite& getCurrent();
		int getLength();
		bool isFinished();
		bool isDone();
	private:
		std::vector<Sprite>* mpSprites;
		bool mLoop, mDone;
		int mCurrent;
		double mTime, mCurrentTime;
};

#endif