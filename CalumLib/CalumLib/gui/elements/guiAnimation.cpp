#include "guiAnimation.h"

#include "game.h"

#include "graphics/animation.h"
#include "graphics/animationManager.h"
#include "graphics/graphicsSystem.h"

GUIAnimation::GUIAnimation(int x, int y, Animation* anim, float scale)
{
	mX = x;
	mY = y;
	mpAni = anim;
	mScale = scale;
}

GUIAnimation::GUIAnimation(int x, int y, const char* animString, float scale)
{
	mX = x;
	mY = y;
	mpAni = Game::pInstance->getAnimationManager()->get(animString);
	mScale = scale;
}

GUIAnimation::~GUIAnimation()
{
	delete mpAni;
}

void GUIAnimation::update(double dt)
{
	mpAni->update(dt);
}

void GUIAnimation::draw()
{
	Game::pInstance->getGraphics()->draw((float)mX, (float)mY, mpAni->getCurrent(), mScale);
}

void GUIAnimation::setFrame(int frame)
{
	mpAni->setFrame(frame);
}