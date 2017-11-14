#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "graphics/animation.h"

#include "utils/stringManager.h"

#include <string>

class AnimationManager : public StringManager<Animation>
{
	public:
		~AnimationManager();

		Animation* get(const std::string& key);
};

#endif