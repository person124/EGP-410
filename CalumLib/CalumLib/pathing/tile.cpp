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
	Game::pInstance->getGraphics()->drawOffset(x * GC::TILE_SIZE, y * GC::TILE_SIZE, mpSprite, GC::TILE_SCALE);
}

void Tile::drawSolidity(int x, int y)
{
	Game::pInstance->getGraphics()->drawOffset(x * GC::TILE_SIZE, y * GC::TILE_SIZE, Tile::mspSolidAnimation->getSprite(mID), GC::TILE_SCALE);
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
	mpSprite = Tile::mspTileAnimation->getSprite(mID);
	mSolid = Tile::mspSolidAnimation->getSprite(mID)->getBlackOrWhite();
}