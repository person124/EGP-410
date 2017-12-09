#include "guiLevel.h"

#include "game.h"
#include "globalConst.h"

#include "events/eventCandyStart.h"
#include "events/eventSystem.h"

#include "graphics/animationManager.h"
#include "graphics/graphicsSystem.h"
#include "graphics/sprite.h"

#include "gui/elements/guiFixedText.h"
#include "gui/elements/guiText.h"

enum ElementsType
{
	SCORE,
	SCORE_TEXT,
	ELEMENT_COUNT
};

GUILevel::GUILevel()
{
	setElementCount(ELEMENT_COUNT);

	mpElements[SCORE] = new GUIFixedText(0, 0, "Score:");
	mpElements[SCORE_TEXT] = new GUIText(75, 0, "0");

	mpOraSpawn = Game::pInstance->getAnimationManager()->get("ora_spawn");
	mRenderSpawn = false;
	mOraX = GC::WINDOW_WIDTH / 2 - mpOraSpawn->getCurrent()->getWidth() / 2;
	mOraY = GC::WINDOW_HEIGHT / 2 - mpOraSpawn->getCurrent()->getHeight() / 2;

	gpEventSystem->addListener(EVENT_CANDY_START, this);
}

GUILevel::~GUILevel()
{
	delete mpOraSpawn;

	gpEventSystem->removeListener(EVENT_CANDY_START, this);
}

void GUILevel::update(double dt)
{
	GUI::update(dt);
	if (mRenderSpawn)
	{
		mpOraSpawn->update(dt);
		if (mpOraSpawn->isFinished())
			mRenderSpawn = false;
	}
}

void GUILevel::draw()
{
	GUI::draw();
	if (mRenderSpawn)
	{
		Game::pInstance->getGraphics()->draw(
			mOraX,
			mOraY,
			mpOraSpawn->getCurrent(),
			1
		);
	}
}

void GUILevel::setScore(int s)
{
	((GUIText*)mpElements[SCORE_TEXT])->updateText(s);
}

void GUILevel::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_CANDY_START)
	{
		mpOraSpawn->setFrame(0);
		mRenderSpawn = true;
	}
}