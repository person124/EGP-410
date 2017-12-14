#include "guiHelp.h"

#include "globalConst.h"

#include "events/eventSwitchState.h"

#include "gui/elements/guiFixedText.h"

enum Elements
{
	RETURN_TO_MAIN_MENU,
	//Help for main game
	IN_GAME,
	MOVEMENT,
	HOW_TO,
	SUPER_CANDY,
	GET_HIGH_SCORE,
	//Help for editor
	IN_EDITOR,
	CAMERA_MOVEMENT,
	RE_SELECT,
	CHANGE_SELECTION,
	LEFT_CLICK,
	RIGHT_CLICK,
	SAVE_AND_LOAD,
	ELEMENT_COUNT
};

GUIHelp::GUIHelp()
{
	setElementCount(ELEMENT_COUNT);
	mpElements[RETURN_TO_MAIN_MENU] = new GUIFixedText(50, GC::WINDOW_HEIGHT - GC::FONT_SIZE, "Return to Main Menu");

	mpElements[IN_GAME] = new GUIFixedText(50, 50,
		"--Game Controls--");
	mpElements[MOVEMENT] = new GUIFixedText(50, 50 + 40,
		"W A S D - Movement");
	mpElements[HOW_TO] = new GUIFixedText(50, 50 + 40 + 40,
		"Move around collecting the clues. Don't let Sheer Heart Attack catch you!");
	mpElements[SUPER_CANDY] = new GUIFixedText(50, 50 + 40 + 40 + 40,
		"Collectint the \"STAND ARROW\" to summon help and overpower Sheer Heart Attack!");
	mpElements[GET_HIGH_SCORE] = new GUIFixedText(50, 50 + 40 + 40 + 40 + 40,
		"Try to ge the highest score you can!");

	mpElements[IN_EDITOR] = new GUIFixedText(50, 300,
		"--Editor Controls--");
	mpElements[CAMERA_MOVEMENT] = new GUIFixedText(50, 300 + 40,
		"Arrow Keys - Move Camera");
	mpElements[RE_SELECT] = new GUIFixedText(50, 300 + 40 + 40,
		"W S - Change Selection Type");
	mpElements[CHANGE_SELECTION] = new GUIFixedText(50, 300 + 40 + 40 + 40,
		"A D - Modify Selected Type Value");
	mpElements[LEFT_CLICK] = new GUIFixedText(50, 300 + 40 + 40 + 40 + 40,
		"Left Click - Place selected tile or spawn point");
	mpElements[RIGHT_CLICK] = new GUIFixedText(50, 300 + 40 + 40 + 40 + 40 + 40,
		"Right Click - Remove selected spawn point");
	mpElements[SAVE_AND_LOAD] = new GUIFixedText(50, 300 + 40 + 40 + 40 + 40 + 40 + 40,
		"Press 'P' to save the map and press '.' to load the map");

	setSelectableCount(1);
	addSelectable(RETURN_TO_MAIN_MENU, new EventSwitchState(STATE_MAIN_MENU));

	refreshSelector();
}

GUIHelp::~GUIHelp()
{
}