#ifndef GUI_IMAGE_H
#define GUI_IMAGE_H

#include "gui/guiElement.h"

class GraphicsBuffer;

class GUIImage : public GUIElement
{
	public:
		GUIImage(int x, int y, GraphicsBuffer* buffer, float scale = 1.0f);
		GUIImage(int x, int y, const char* bufferString, float scale = 1.0f);
		~GUIImage();

		void draw();
	private:
		GraphicsBuffer* mpBuffer;
		float mScale;
};

#endif