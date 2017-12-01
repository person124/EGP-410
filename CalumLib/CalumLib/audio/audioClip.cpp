#include "audioClip.h"

#include <allegro5/allegro_audio.h>

AudioClip::AudioClip()
{
}

AudioClip::AudioClip(const std::string& path)
{
	mIsStream = false;

	mpClip = al_load_sample(path.c_str());
	mpStream = NULL;
	mpID = new ALLEGRO_SAMPLE_ID;
}

AudioClip::AudioClip(const std::string& path, ALLEGRO_MIXER* mixer)
{
	mIsStream = true;

	mpStream = al_load_audio_stream(path.c_str(), 4, 2048);
	al_set_audio_stream_playmode(mpStream, ALLEGRO_PLAYMODE_LOOP);
	stop();
	
	al_attach_audio_stream_to_mixer(mpStream, mixer);

	mpClip = NULL;
	mpID = NULL;
}

AudioClip::~AudioClip()
{
	if (mIsStream)
		al_destroy_audio_stream(mpStream);
	else
	{
		al_destroy_sample(mpClip);
		delete mpID;
	}
}

void AudioClip::play(bool loop)
{
	if (mIsStream)
		al_set_audio_stream_playing(mpStream, true);
	else
		al_play_sample(mpClip, 1.0f, 0.0f, 1.0f, loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE, mpID);
}

void AudioClip::stop()
{
	if (mIsStream)
		al_set_audio_stream_playing(mpStream, false);
	else
		al_stop_sample(mpID);
}

void AudioClip::rewind()
{
	if (mIsStream)
		al_rewind_audio_stream(mpStream);
}