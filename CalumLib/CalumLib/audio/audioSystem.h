#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include "audio/audioClip.h"

#include "utils/stringManager.h"

class AudioSystem : public StringManager<AudioClip>
{
	public:
		bool init();

		void registerClip(const std::string& key, const std::string& path);
		void registerStream(const std::string& key, const std::string& path);
	private:
};

#endif