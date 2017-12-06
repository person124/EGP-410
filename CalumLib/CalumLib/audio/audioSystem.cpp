#include "audioSystem.h"

#include "globalConst.h"

#include "graphics/graphicsSystem.h"

#include "utils/ioUtils.h"

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

bool AudioSystem::init()
{
	if (!al_install_audio())
	{
		IOUtils::errorInitReport("audio addon");
		return false;
	}

	if (!al_reserve_samples(GC::AUDIO_COUNT))
	{
		IOUtils::errorInitReport("audio samples allocation");
		return false;
	}

	if (!al_init_acodec_addon())
	{
		IOUtils::errorInitReport("audio codec");
		return false;
	}

	return true;
}

void AudioSystem::registerClip(const std::string& key, const std::string& path)
{
	AudioClip* clip = new AudioClip(path);
	add(key, clip);
}

void AudioSystem::registerStream(const std::string& key, const std::string& path)
{
	AudioClip* clip = new AudioClip(path, al_get_default_mixer());
	add(key, clip);
}

void AudioSystem::play(const std::string& key, bool loop)
{
	get(key)->play(loop);
}