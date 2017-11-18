#include "guiEditor.h"

#include "gui/elements/guiFixedText.h"

GUIEditor::GUIEditor()
{
	setElementCount(1);
	mpElements[0] = new GUIFixedText(0, 0, "Merpa!");
}