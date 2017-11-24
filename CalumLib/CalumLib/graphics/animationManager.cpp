#include "animationManager.h"

AnimationManager::~AnimationManager()
{
	std::map<std::string, Animation*>::iterator iter;

	//Delete all of the original sprites that are created
	for (iter = mItems.begin(); iter != mItems.end(); iter++)
		iter->second->destroy();
}

Animation* AnimationManager::get(const std::string& key)
{
	if (key == "")
		return NULL;

	return new Animation(mItems.at(key));
}