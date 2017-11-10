#include "audioSystem.h"

#include "globalConst.h"

#include "graphics/graphicsSystem.h"

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

bool AudioSystem::init()
{
	if (!al_install_audio())
	{
		initError("audio addon");
		return false;
	}

	if (!al_reserve_samples(AUDIO_SAMPLES))
	{
		initError("audio samples allocation");
		return false;
	}

	if (!al_init_acodec_addon())
	{
		initError("audio codec");
		return false;
	}

	return true;
}

void AudioSystem::registerClip(std::string key, std::string path)
{
	AudioClip* clip = new AudioClip(path);
	add(key, clip);
}

void AudioSystem::registerStream(std::string key, std::string path)
{
	AudioClip* clip = new AudioClip(path, al_get_default_mixer());
	add(key, clip);
}