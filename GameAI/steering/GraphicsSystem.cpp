#include <allegro5/allegro.h>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"

//For random
#include "EventSystem.h"
#include "EventSetColor.h"
#include <cmath>

GraphicsSystem::GraphicsSystem()
	:mpDisplay(NULL)
	,mpBackBuffer(NULL)
	,mWidth(0)
	,mHeight(0)
{
	gpEventSystem->addListener(EVENT_CHANGE_COLOR, this);
	gpEventSystem->addListener(EVENT_SET_COLOR, this);
	handleEvent(EventSetColor());
}

GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}

bool GraphicsSystem::init( int width, int height )
{
	mWidth = width;
	mHeight = height;
	mpDisplay = al_create_display(width, height);
	if(!mpDisplay) 
	{
		fprintf(stderr, "GraphicsSystem::failed to create display!\n");
		return false;
	}
		
	//get the backbuffer
	ALLEGRO_BITMAP* pBackBuffer = al_get_backbuffer( mpDisplay );

	//set the back buffer as the target bitmap
	al_set_target_bitmap( pBackBuffer );

	//create the GraphicsBuffer backbuffer
	mpBackBuffer = new GraphicsBuffer( pBackBuffer );

	//al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgb(255,255,255));

	return true;
}

void GraphicsSystem::cleanup()
{
	al_destroy_display( mpDisplay );
	mpDisplay = NULL;

	mpBackBuffer->invalidate();
	delete mpBackBuffer;
	mpBackBuffer = NULL;
}

void GraphicsSystem::swap()
{
	al_flip_display();
}

void GraphicsSystem::wrapCoordinates( Vector2& vector )
{
	if( vector.x < 0.0f )
	{
		vector.x = getWidth() - 1.0f;
	}
	else if( vector.x >= getWidth() )
	{
		vector.x = 0.0f;
	}

	if( vector.y < 0.0f )
	{
		vector.y = getHeight() - 1.0f;
	}
	else if( vector.y >= getHeight() )
	{
		vector.y = 0.0f;
	}
}

//static function
ALLEGRO_BITMAP* GraphicsSystem::switchTargetBitmap( ALLEGRO_BITMAP* pNewTarget )
{
	//get old target bitmap
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	//set dest to be the target
	al_set_target_bitmap( pNewTarget );

	return pOldTarget;
}

void GraphicsSystem::drawText(float x, float y, std::string text, int flag)
{
	al_draw_text(gpGame->getFont(), mTextColor, x, y, flag, text.c_str());
}

void GraphicsSystem::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EVENT_CHANGE_COLOR)
		mTextColor = al_map_rgb(rand() % 255, rand() % 255, rand() % 255);
	else if (theEvent.getType() == EVENT_SET_COLOR)
		mTextColor = al_map_rgb(255, 255, 255);
}