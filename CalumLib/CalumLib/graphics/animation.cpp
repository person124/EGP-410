#include "animation.h"

#include "graphics/sprite.h"

Animation::Animation(std::vector<Sprite*> sprites, double time, bool loop)
{
	mCurrentTime = 0;
	mCurrent = 0;
	mLoop = loop;
	setSpeed(time);

	mSprites = sprites;

	mDone = false;
}

Animation::Animation(double time, bool loop)
{
	mCurrentTime = 0;
	mCurrent = 0;
	mLoop = loop;
	setSpeed(time);

	mSprites = std::vector<Sprite*>();

	mDone = false;
}

Animation::Animation(Animation* ani)
{
	mCurrentTime = 0;
	mCurrent = 0;

	mLoop = ani->mLoop;
	setSpeed(ani->mTime);

	mSprites = ani->mSprites;

	mDone = false;
}

Animation::~Animation()
{
}

void Animation::addSprite(Sprite* sprite)
{
	mSprites.push_back(sprite);
}

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

void Animation::destroy()
{
	for (int i = 0; i < getLength(); i++)
		delete mSprites.at(i);
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
	mDone = false;
}

double Animation::getSpeed()
{
	return mTime;
}

Sprite* Animation::getCurrent()
{
	return mSprites.at(mCurrent);
}

Sprite* Animation::getSprite(int frame)
{
	if (frame < 0)
		frame = 0;
	else if (frame > getLength())
		frame = getLength() - 1;
	return mSprites.at(frame);
}

int Animation::getLength()
{
	return mSprites.size();
}

bool Animation::isFinished()
{
	return mDone || mCurrent >= getLength();
}