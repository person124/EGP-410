#ifndef AUDIO_CLIP_H
#define AUDIO_CLIP_H

#include "utils/trackable.h"

#include <string>

struct ALLEGRO_MIXER;
struct ALLEGRO_SAMPLE;
struct ALLEGRO_AUDIO_STREAM;

class AudioClip : public Trackable
{
	friend class AudioSystem;
	public:
		AudioClip();
		~AudioClip();

		void play(bool loop);
		void stop();
		void rewind();
	private:
		AudioClip(const std::string& path);
		AudioClip(const std::string& path, ALLEGRO_MIXER* mixer);

		ALLEGRO_SAMPLE* mpClip;
		ALLEGRO_AUDIO_STREAM* mpStream;
		bool mIsStream;
};

#endif