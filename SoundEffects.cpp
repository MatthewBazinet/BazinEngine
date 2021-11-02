#include "SoundEffects.h"

SoundEffects::SoundEffects()
{
	
	SDL_Init(SDL_INIT_AUDIO);


	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		Log::FatalError("Audio failed to initialize", "SoundEffects.cpp", __LINE__);
	}
}

SoundEffects::~SoundEffects()
{
}

void SoundEffects::AddSoundEffects(const char* path)
{
	Mix_Chunk* tmpChunk = Mix_LoadWAV(path);
	if (tmpChunk != nullptr) {
		listOfSoundEffects.push_back(tmpChunk);
		std::cout << (listOfSoundEffects.size() - 1) << "Sound is Ready, path " << path << '\n';
	}
	else {
		Log::FatalError("Audio failed to initialize", "SoundEffects.cpp", __LINE__);
	}
}

void SoundEffects::playSoundEffect(const int choice) const
{
 	if (choice > listOfSoundEffects.size() - 1) {
		std::cout << "Sound out of range. \n";
	}
	Mix_Volume(-1, MIX_MAX_VOLUME / 10);
	Mix_PlayChannel(-1, listOfSoundEffects[choice], 0);

}
