#include "guiEditor.h"

#include "globalConst.h"

#include "gui/elements/guiAnimation.h"
#include "gui/elements/guiFixedText.h"
#include "gui/elements/guiText.h"
#include "gui/elements/guiImage.h"

#include "gameMode/editor.h"

enum ElementsTypes
{
	HEADER_TEXT,
	CURRENT_TILE,
	CURRENT_TILE_ANIM,
	CURRENT_SPAWN,
	CURRENT_SPAWN_ANIM,
	ARROW,
	SAVE_TEXT,
	LOAD_TEXT,
	CURRENT_WIDTH,
	CURRENT_WIDTH_TEXT,
	CURRENT_HEIGHT,
	CURRENT_HEIGHT_TEXT,
	MAX_ELEMENTS
};

GUIEditor::GUIEditor()
{
	setElementCount(MAX_ELEMENTS);
	mpElements[HEADER_TEXT] = new GUIFixedText(600, 0, "Edit Mode");

	mpElements[CURRENT_TILE] = new GUIFixedText(0, 5, "Current Tile:");
	mpElements[CURRENT_TILE_ANIM] = new GUIAnimation(160, 0, "tiles", 2);

	mpElements[CURRENT_SPAWN] = new GUIFixedText(0, 45, "Current Spawn:");
	mpElements[CURRENT_SPAWN_ANIM] = new GUIAnimation(170, 40, "editor_spawns", 2);

	mpElements[CURRENT_WIDTH] = new GUIFixedText(0, 85, "Current Width:");
	mpElements[CURRENT_WIDTH_TEXT] = new GUIText(170, 85, "30");

	mpElements[CURRENT_HEIGHT] = new GUIFixedText(0, 125, "Current Height:");
	mpElements[CURRENT_HEIGHT_TEXT] = new GUIText(180, 125, "30");

	mpElements[ARROW] = new GUIImage(0, 0, "editor_arrow", 2);

	mpElements[SAVE_TEXT] = new GUIFixedText(0, GC::WINDOW_HEIGHT, "Saved to editor.JO");
	mpElements[LOAD_TEXT] = new GUIFixedText(0, GC::WINDOW_HEIGHT, "Loaded from editor.JO");
}

void GUIEditor::changeSelected(int selected)
{
	int toMatch;
	if (selected == TILE)
		toMatch = CURRENT_TILE_ANIM;
	else if (selected == SPAWNS)
		toMatch = CURRENT_SPAWN_ANIM;
	else if (selected == MODIFY_WIDTH)
		toMatch = CURRENT_WIDTH_TEXT;
	else if (selected == MODIFY_HEIGHT)
		toMatch = CURRENT_HEIGHT_TEXT;

	int x = mpElements[toMatch]->getX() + 40;
	int y = mpElements[toMatch]->getY();

	mpElements[ARROW]->setX(x);
	mpElements[ARROW]->setY(y);
}

void GUIEditor::setTileFrame(int frame)
{
	((GUIAnimation*)mpElements[CURRENT_TILE_ANIM])->setFrame(frame);
}

void GUIEditor::setSpawnFrame(int frame)
{
	((GUIAnimation*)mpElements[CURRENT_SPAWN_ANIM])->setFrame(frame);
}

void GUIEditor::setSize(int type, int size)
{
	GUIText* text = NULL;

	if (type == MODIFY_WIDTH)
		text = (GUIText*)mpElements[CURRENT_WIDTH_TEXT];
	else if (type == MODIFY_HEIGHT)
		text = (GUIText*)mpElements[CURRENT_HEIGHT_TEXT];

	if (text != NULL)
		text->updateText(size);
}

void GUIEditor::renderSaveMessage(bool val)
{
	mpElements[SAVE_TEXT]->setY(GC::WINDOW_HEIGHT - (val * GC::FONT_SIZE));
}

void GUIEditor::renderLoadMessage(bool val)
{
	mpElements[LOAD_TEXT]->setY(GC::WINDOW_HEIGHT - (val * GC::FONT_SIZE));
}