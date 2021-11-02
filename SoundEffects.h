#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H

#include <SDL.h>
#include <vector>
#include <SDL_mixer.h>
#include "Engine/Core/Log.h"
class SoundEffects
{
public:
	SoundEffects();
	~SoundEffects();

	void AddSoundEffects(const char* path);
	void playSoundEffect(const int choice)const;
private:
	std::vector<Mix_Chunk*> listOfSoundEffects;
};
#endif