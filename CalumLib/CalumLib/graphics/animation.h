#ifndef ANIMATION_H
#define ANIMATION_H

#include "utils/trackable.h"

#include <vector>

class Sprite;

class Animation : public Trackable
{
	public:
		//Constructors
		Animation(std::vector<Sprite*> sprites, double time, bool loop = true);
		Animation(double time, bool loop = true);
		Animation(Animation* ani);
		~Animation();

		//Misc.
		void addSprite(Sprite* sprite);
		void update(const double& dt);
		void destroy();

		//Setters
		void setSpeed(double newSpeed);
		void setFrame(int frame);

		//Getters
		double getSpeed();
		Sprite* getCurrent();
		Sprite* getSprite(int frame);
		int getLength();
		bool isFinished();
	private:
		std::vector<Sprite*> mSprites;
		bool mLoop, mDone;
		int mCurrent;
		double mTime, mCurrentTime;
};

#endif