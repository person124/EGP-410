#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include "stringManager.h"

#include "audio/audioClip.h"

class AudioSystem : public StringManager<AudioClip>
{
	public:
		bool init();

		void registerClip(std::string key, std::string path);
		void registerStream(std::string key, std::string path);
	private:
};

#endif