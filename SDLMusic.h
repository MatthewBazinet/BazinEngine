#ifndef SDLMUSIC_H
#define SDLMUSIC_H
#include <vector>
#include <SDL_mixer.h>
class SDLMusic
{
public:

	SDLMusic();

	void addMusicTrack(const char* path);

	void playMusicTrack(const int which);

	void Play_Pause();

private:

	std::vector<Mix_Music*> m_Musics;

	bool m_Paused = false;

	bool m_Playing = false;

};
#endif
