#ifndef SPRITE_H
#define SPRITE_H

#include "graphicsBuffer.h"
#include "color.h"

#include <Trackable.h>

class Sprite : public Trackable
{
    friend class GraphicsSystem;
    public:
		Sprite();
		Sprite(GraphicsBuffer* buffer, int sX, int sY, int width, int height);

		//Getters
        int getWidth();
        int getHeight();
		GraphicsBuffer*& getBuffer();
		int startX();
		int startY();
    private:
        GraphicsBuffer* mpBuffer;
		int mStartX, mStartY, mWidth, mHeight;
};

#endif