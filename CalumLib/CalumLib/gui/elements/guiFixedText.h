#ifndef GUI_FIXED_TEXT_H
#define GUI_FIXED_TEXT_H

#include "gui/guiElement.h"

#include <string>

class GUIFixedText : public GUIElement
{
	public:
		GUIFixedText(int x, int y, const std::string& text);
		~GUIFixedText();

		void draw();
	protected:
		GUIFixedText()
		{
			mX = 0;
			mY = 0;
			mText = "";
		}

		std::string mText;
};

#endif