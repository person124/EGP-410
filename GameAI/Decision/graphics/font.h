#ifndef FONT_H
#define FONT_H

#include <string>

#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

#include <Trackable.h>

class Font : public Trackable
{
	friend class GraphicsSystem;
	public:
		Font(int size, const std::string& path);
		~Font();

		int getSize();
		std::string getFilePath();
	private:
		ALLEGRO_FONT* mpFont;
		std::string mFilePath;
		int mSize;
};

#endif