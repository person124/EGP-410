#include "animationManager.h"

Animation* AnimationManager::get(const std::string& key)
{
	return new Animation(mItems.at(key));
}