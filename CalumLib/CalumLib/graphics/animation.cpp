#include "animation.h"

Animation::Animation(std::vector<Sprite>* sprites, double time, bool loop)
{
	mCurrentTime = 0;
	mCurrent = 0;
	mLoop = loop;
	setSpeed(time);

	mpSprites = sprites;

	mDone = false;
}

Animation::Animation(double time, bool loop)
{
	mCurrentTime = 0;
	mCurrent = 0;
	mLoop = loop;
	setSpeed(time);

	mpSprites = new std::vector<Sprite>();

	mDone = false;
}

Animation::Animation(Animation* ani)
{
	mCurrentTime = 0;
	mCurrent = 0;

	mLoop = ani->mLoop;
	setSpeed(ani->mTime);

	mpSprites = ani->mpSprites;

	mDone = false;
}

Animation::~Animation()
{
}

void Animation::addSprite(Sprite& sprite)
{
	mpSprites->push_back(sprite);
}

#include "game.h"
#include "audio/audioSystem.h"

void Animation::update(double dt)
{
	if (mDone)
		return;

	mCurrentTime += dt;
	
	if (mCurrentTime >= mTime)
	{
		mCurrentTime = 0;
		mCurrent++;

		if (isFinished()) {
			if (!mLoop)
			{
				mDone = true;
				mCurrent--;
			}
			else
				mCurrent = 0;
		}
	}
}

void Animation::setSpeed(double newSpeed)
{
	mTime = newSpeed;
	if (mTime < 0)
		mTime = 0;
}

void Animation::setFrame(int frame)
{
	if (frame < 0)
		frame = 0;
	else if (frame > getLength())
		frame = getLength() - 1;

	mCurrent = frame;
}

double Animation::getSpeed()
{
	return mTime;
}

Sprite& Animation::getCurrent()
{
	return mpSprites->at(mCurrent);
}

int Animation::getLength()
{
	return mpSprites->size();
}

bool Animation::isFinished()
{
	return mCurrent >= getLength();
}

bool Animation::isDone()
{
	return mDone;
}