#include "SoundEffects.h"
#include <SDL.h>
#include <iostream>
#include "SDLInit.h"


SoundEffects::SoundEffects()
{
	SDLInit::initSDLSound();
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
