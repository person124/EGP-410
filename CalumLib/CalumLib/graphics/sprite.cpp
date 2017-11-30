#include "sprite.h"

#include "graphics/graphicsBuffer.h"
#include "graphics/color.h"

#include <allegro5/bitmap.h>

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
	ALLEGRO_BITMAP* subMap = al_create_sub_bitmap(buffer->mpBitmap, sX, sY, width, height);

	mpBuffer = new GraphicsBuffer(subMap);

	mStartX = sX;
	mStartY = sY;
	mWidth = width;
	mHeight = height;

	mIsFlipped = flipped;

	Color* tempColor = buffer->getPixel(sX + 1, sY + 1);
	mIsBlack = tempColor->isBlack();
	delete tempColor;
}

Sprite::~Sprite()
{
	//delete mpBuffer->mpBitmap;
	delete mpBuffer;
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