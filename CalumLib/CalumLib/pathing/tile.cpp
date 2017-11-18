#include "tile.h"

#include "globalConst.h"
#include "game.h"

#include "graphics/graphicsSystem.h"
#include "graphics/animationManager.h"
#include "graphics/animation.h"
#include "graphics/sprite.h"

Animation* Tile::mspTileAnimation = NULL;
Animation* Tile::mspSolidAnimation = NULL;

Tile::Tile(int id)
{
	if (Tile::mspTileAnimation == NULL)
		Tile::mspTileAnimation = Game::pInstance->getAnimationManager()->get("tiles");

	if (Tile::mspSolidAnimation == NULL)
		Tile::mspSolidAnimation = Game::pInstance->getAnimationManager()->get("tiles_solid");

	setID(id);
}

Tile::~Tile()
{
	if (Tile::mspTileAnimation != NULL)
	{
		delete Tile::mspTileAnimation;
		Tile::mspTileAnimation = NULL;
	}

	if (Tile::mspSolidAnimation != NULL)
	{
		delete Tile::mspSolidAnimation;
		Tile::mspSolidAnimation = NULL;
	}
}

void Tile::draw(int x, int y)
{
	Game::pInstance->getGraphics()->drawOffset(x * TILE_SIZE, y * TILE_SIZE, mpSprite, TILE_SCALE);
}

bool Tile::isSolid()
{
	return mSolid;
}

int Tile::getID()
{
	return mID;
}

void Tile::setID(int id)
{
	mID = id;

	Tile::mspTileAnimation->setFrame(id);
	Tile::mspSolidAnimation->setFrame(0);

	mpSprite = Tile::mspTileAnimation->getCurrent();
	mSolid = Tile::mspSolidAnimation->getCurrent()->getBlackOrWhite();
}