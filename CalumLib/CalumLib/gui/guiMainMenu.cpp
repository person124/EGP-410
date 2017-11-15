#include "guiMainMenu.h"

#include "events/eventQuit.h"

#include "gui/elements/guiFixedText.h"
#include "gui/elements/guiImage.h"

GUIMainMenu::GUIMainMenu()
{
	mElementCount = 6;
	mpElements = new GUIElement*[mElementCount];

	//Background
	mpElements[0] = new GUIImage(0, 0, "background", 1.5f);
	mpElements[5] = new GUIFixedText(150, 300, "Heart Attack Escape!");

	mpElements[1] = new GUIFixedText(150, 350, "Start Game");
	mpElements[2] = new GUIFixedText(150, 400, "Options");
	mpElements[3] = new GUIFixedText(150, 450, "Editor");
	mpElements[4] = new GUIFixedText(150, 500, "Quit");

	setMax(4);
	addSelectable(1, new EventQuit());
	addSelectable(2, new EventQuit());
	addSelectable(3, new EventQuit());
	addSelectable(4, new EventQuit());

	refreshSelector();
}