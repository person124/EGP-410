#include "guiImage.h"

#include "game.h"

#include "graphics/graphicsSystem.h"
#include "graphics/graphicsBufferManager.h"
#include "graphics/graphicsBuffer.h"

GUIImage::GUIImage(int x, int y, GraphicsBuffer* buffer, float scale)
{
	mX = x;
	mY = y;
	mpBuffer = buffer;
	mScale = scale;
}

GUIImage::GUIImage(int x, int y, const char* bufferString, float scale)
{
	mX = x;
	mY = y;
	mpBuffer = Game::pInstance->getBufferManager()->get(bufferString);
	mScale = scale;
}

GUIImage::~GUIImage()
{
}

void GUIImage::draw()
{
	Game::pInstance->getGraphics()->draw((float)mX, (float)mY, mpBuffer, mScale);
}