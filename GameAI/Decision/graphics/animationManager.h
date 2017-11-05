#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "../stringManager.h"
#include "animation.h"

#include <string>

class AnimationManager : public StringManager<Animation>
{
	public:
		Animation* get(const std::string& key);
};

#endif