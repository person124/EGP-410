#include "tile.h"

#include "../globalConst.h"
#include "../game.h"

#include "../graphics/graphicsSystem.h"
#include "../graphics/animationManager.h"
#include "../graphics/animation.h"

Tile::Tile(bool solid)
{
	mSolid = solid;
	mpAnimation = Game::pInstance->getAnimationManager()->get("tile");
	mpAnimation->setFrame(mSolid);
}

Tile::~Tile()
{
	delete mpAnimation;
}

void Tile::draw(int x, int y)
{
	Game::pInstance->getGraphics()->draw(x * TILE_SIZE, y * TILE_SIZE, mpAnimation->getCurrent(), TILE_SCALE);
}

bool Tile::isSolid()
{
	return mSolid;
}

void Tile::setSolid(bool value)
{
	mSolid = value;
}