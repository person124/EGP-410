#include "guiSelectLevel.h"

#include "globalConst.h"

#include "events/eventSwitchState.h"
#include "events/eventLoadLevel.h"

#include "gui/elements/guiFixedText.h"

#include "utils/ioUtils.h"

#include <string>

GUISelectLevel::GUISelectLevel(const char* levelPath)
{
	unsigned int size;
	std::string* levels = NULL;
	IOUtils::getLevels(levelPath, levels, size);

	//Then chart them out
	setElementCount(2 + size);
	mpElements[0] = new GUIFixedText(0, 0, "Select Level");
	mpElements[1] = new GUIFixedText(50, WINDOW_HEIGHT - 20, "Back to Main Menu");

	setSelectableCount(1 + size);
	addSelectable(1, new EventSwitchState(STATE_MAIN_MENU));


	for (unsigned int i = 0; i < size; i++)
	{
		const char* lName = levels[i].c_str();

		mpElements[2 + i] = new GUIFixedText(50, 20 * (i + 1), lName);
		addSelectable(2 + i, new EventLoadLevel(lName));
	}

	delete[] levels;

	
	refreshSelector();
}