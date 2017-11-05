#include "animation.h"

Animation::Animation(std::vector<Sprite>*& sprites, double time, bool loop)
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

Animation::Animation(Animation*& ani)
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

void Animation::update(double dt)
{
	if (mDone)
		return;

	mCurrentTime += dt;
	
	if (mCurrentTime >= mTime)
	{
		mCurrentTime -= mTime;
		mCurrent++;

		if (isFinished()) {
			mCurrent = 0;
			if (!mLoop)
				mDone = true;
		}
	}
}

void Animation::setSpeed(double newSpeed)
{
	mTime = newSpeed;
	if (mTime < 0)
		mTime = 0;
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
	return mpSprites->capacity();
}

bool Animation::isFinished()
{
	return mCurrent >= getLength();
}

bool Animation::isDone()
{
	return mDone;
}