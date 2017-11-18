#include "tile.h"

#include "globalConst.h"
#include "game.h"

#include "graphics/graphicsSystem.h"
#include "graphics/animationManager.h"
#include "graphics/animation.h"
#include "graphics/sprite.h"

Animation* Tile::mspSolidAnimation = NULL;

Tile::Tile(int id)
{
	if (Tile::mspSolidAnimation == NULL)
		Tile::mspSolidAnimation = Game::pInstance->getAnimationManager()->get("tiles_solid");

	mpAnimation = Game::pInstance->getAnimationManager()->get("tiles");
	setID(id);
}

Tile::~Tile()
{
	if (Tile::mspSolidAnimation != NULL)
	{
		delete Tile::mspSolidAnimation;
		Tile::mspSolidAnimation = NULL;
	}

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

int Tile::getID()
{
	return mID;
}

void Tile::setID(int id)
{
	mID = id;

	mpAnimation->setFrame(id);
	Tile::mspSolidAnimation->setFrame(0);
	mSolid = Tile::mspSolidAnimation->getCurrent()->getBlackOrWhite();
}