#ifndef COLOR_H
#define COLOR_H

#include <Trackable.h>

struct ALLEGRO_COLOR;

class Color : public Trackable
{
	friend class GraphicsSystem;
	friend class GraphicsBuffer;
	public:
		Color(int r, int g, int b);
		Color(float r, float g, float b);
		~Color();

		void setAlpha(float a);
		void setAlpha(int a);
	private:
		ALLEGRO_COLOR* mColor;
};

#endif