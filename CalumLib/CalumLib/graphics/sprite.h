#ifndef SPRITE_H
#define SPRITE_H

#include "utils/trackable.h"

class GraphicsBuffer;

class Sprite : public Trackable
{
    //friend class GraphicsSystem;
    public:
		Sprite();
		Sprite(GraphicsBuffer* buffer, int sX, int sY, int width, int height, bool flipped = false);

		//Getters
        int getWidth();
        int getHeight();
		GraphicsBuffer* getBuffer();
		int startX();
		int startY();
		bool isFlipped();

		// Specifically for tile solidity
		bool getBlackOrWhite();
    private:
        GraphicsBuffer* mpBuffer;
		int mStartX, mStartY, mWidth, mHeight;
		bool mIsFlipped;

		bool mIsBlack;
};

#endif