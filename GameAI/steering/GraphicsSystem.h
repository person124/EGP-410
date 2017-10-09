#pragma once

#include <allegro5/allegro.h>
#include <allegro5\allegro_font.h>

#include "EventListener.h"

#include "Phys.h"

#include <string>

class GraphicsBuffer;

class GraphicsSystem:public EventListener
{
public:
	GraphicsSystem();
	~GraphicsSystem();

	bool init( int width, int height );
	void cleanup();

	void swap();
	void wrapCoordinates( Vector2& vector );//change the x and y values in the vector to keep them on the visible screen

	//accessors
	int getWidth() const { return mWidth; };
	int getHeight() const { return mHeight; };
	ALLEGRO_DISPLAY* getDisplay() const { return mpDisplay; };
	inline GraphicsBuffer* getBackBuffer() { return mpBackBuffer; };

	static ALLEGRO_BITMAP* switchTargetBitmap( ALLEGRO_BITMAP* pNewTarget );//return old target

	//Functions for drawing text
	void drawText(float x, float y, std::string text, int flag = ALLEGRO_ALIGN_CENTER);

	void handleEvent(const Event& theEvent);
private:
	ALLEGRO_DISPLAY* mpDisplay;
	GraphicsBuffer* mpBackBuffer;
	int mWidth;
	int mHeight;

	ALLEGRO_COLOR mTextColor;
};