#include "gameOver.h"

#include "game.h"
#include "globalConst.h"

#include "audio/audioSystem.h"

#include "events/eventSystem.h"
#include "events/eventSwitchState.h"
#include "events/eventKeypress.h"

#include "graphics/color.h"
#include "graphics/graphicsSystem.h"
#include "graphics/animationManager.h"

#include "gui/guiGameOver.h"

#include "utils/timer.h"

GameOver::GameOver()
{
	mpGUI = new GUIGameOver();

	mpAudio = Game::pInstance->getAudio()->get("bites_the_dust");
	mpTimer = NULL;

	mpPlayer = Game::pInstance->getAnimationManager()->get("player_front");

	mWMid = WINDOW_WIDTH / 2;
	mHMid = WINDOW_HEIGHT / 2;
	mpColor = new Color(0, 0, 0);

	mAnimationDone = false;

	gpEventSystem->addListener(EVENT_KEYPRESS, this);
}

GameOver::~GameOver()
{
	gpEventSystem->removeListener(EVENT_KEYPRESS, this);

	delete mpTimer;

	delete mpPlayer;

	delete mpColor;
}

void GameOver::update(double dt)
{
	if (mAnimationDone)
	{
		return;
	}

	mpPlayer->update(dt);

	if (mpTimer == NULL)
	{
		mpTimer = new Timer();
		mpAudio->play(false);
		mpTimer->start();
		return;
	}

	double time = mpTimer->getElapsedTime();
	if (time >= 3)
	{
		mpGUI->update(dt);
	}
	else if (time >= 8.7)
	{
		mpTimer->stop();
	}
}

void GameOver::draw()
{
	if (mAnimationDone)
	{

		return;
	}

	double time = 0;

	if (mpTimer != NULL)
	{
		time = mpTimer->getElapsedTime();
		if (time >= 2.5)
		{
			mpGUI->draw();
			if (time >= 3.7)
				Game::pInstance->getGraphics()->drawCircle(mWMid, mHMid, WINDOW_WIDTH * ((time - 3.7) / 3.0), *mpColor);
		}
	}

	double scale = (time < 4.9) ? 0 : ((time - 4.9) / (6.3 - 4.9));
	if (time > 6.3)
		scale = 1;
	Game::pInstance->getGraphics()->draw(mWMid * scale, mHMid * scale, mpPlayer->getCurrent(), TILE_SCALE);

	if (time >= 4.5)
		Game::pInstance->getGraphics()->drawCircle(mWMid + 5, mHMid + 5, 50, *mpColor);
}

void GameOver::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_KEYPRESS)
	{
		const EventKeypress& e = static_cast<const EventKeypress&>(theEvent);

		if (e.getKey() == KEYS_CONFIRM)
		{
			mpAudio->stop();
			gpEventSystem->fireEvent(EventSwitchState(STATE_MAIN_MENU));
		}
	}
}