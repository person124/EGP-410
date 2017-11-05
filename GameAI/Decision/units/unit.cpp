#include "unit.h"

#include "../game.h"

#include "../graphics/graphicsSystem.h"
#include "../graphics/animationManager.h"

Unit::Unit(Animation* animation, int x, int y)
{
    mpAnimation = animation;
    mX = x;
    mY = y;
}

Unit::Unit(const std::string& animationKey, int x, int y)
{
	mpAnimation = Game::pInstance->getAnimationManager()->get(animationKey);
	mX = x;
	mY = y;
}

Unit::~Unit()
{
	delete mpAnimation;
}

void Unit::update(double dt)
{
    mpAnimation->update(dt);
}

void Unit::draw()
{
	Game::pInstance->getGraphics()->draw(mX, mY, mpAnimation->getCurrent());
}

void Unit::setLocation(int x, int y)
{
	mX = x;
	mY = y;
}

int Unit::getX()
{
	return mX;
}

int Unit::getY()
{
	return mY;
}

Animation*& Unit::getAnimation()
{
	return mpAnimation;
}

bool Unit::isInside(int x, int y)
{
	Sprite sprite = mpAnimation->getCurrent();
	return x >= mX && x <= mX + sprite.getWidth() && y >= mY && y <= mY + sprite.getHeight();
}

bool Unit::operator==(Unit& unit)
{
	return mX == unit.mX && mY == unit.mY && mpAnimation == unit.mpAnimation;
}