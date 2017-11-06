#include "sprite.h"

Sprite::Sprite()
{
	mpBuffer = NULL;

	mStartX = 0;
	mStartY = 0;
	mWidth = 0;
	mHeight = 0;
}

Sprite::Sprite(GraphicsBuffer* buffer, int sX, int sY, int width, int height)
{
	mpBuffer = buffer;

	mStartX = sX;
	mStartY = sY;
	mWidth = width;
	mHeight = height;
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