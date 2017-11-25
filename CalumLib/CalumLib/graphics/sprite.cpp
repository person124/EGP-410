#include "sprite.h"

#include "graphics/graphicsBuffer.h"
#include "graphics/color.h"

Sprite::Sprite()
{
	mpBuffer = NULL;

	mStartX = 0;
	mStartY = 0;
	mWidth = 0;
	mHeight = 0;

	mIsFlipped = false;

	mIsBlack = true;
}

Sprite::Sprite(GraphicsBuffer* buffer, int sX, int sY, int width, int height, bool flipped)
{
	mpBuffer = buffer;

	mStartX = sX;
	mStartY = sY;
	mWidth = width;
	mHeight = height;

	mIsFlipped = flipped;

	Color* tempColor = mpBuffer->getPixel();
	mIsBlack = tempColor->isBlack();
	delete tempColor;
}

GraphicsBuffer* Sprite::getBuffer()
{
	return mpBuffer;
}

int Sprite::getWidth()
{
	return mWidth;
}

int Sprite::getHeight()
{
	return mHeight;
}

int Sprite::startX()
{
	return mStartX;
}

int Sprite::startY()
{
	return mStartY;
}

bool Sprite::isFlipped()
{
	return mIsFlipped;
}

bool Sprite::getBlackOrWhite()
{
	return mIsBlack;
}