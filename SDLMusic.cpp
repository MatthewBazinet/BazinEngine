#include "SDLMusic.h"
#include "SDLInit.h"
#include <SDL.h>

SDLMusic::SDLMusic()
{
    SDLInit::initSDLSound();
}

void SDLMusic::addMusicTrack(const char* path)
{
    Mix_Music* tmp_music = Mix_LoadMUS(path);

    if (tmp_music != nullptr)
    {
        m_Musics.push_back(tmp_music);
    }
    else
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't load audio: %s",
            Mix_GetError());
    }
}

void SDLMusic::playMusicTrack(const int which)
{
    if (which > m_Musics.size())
    {
        return;
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME / 10);
    Mix_PlayMusic(m_Musics.at(which), -1);

    m_Playing = true;

}

void SDLMusic::Play_Pause()
{
    if (m_Playing && !m_Paused)
    {
        Mix_PauseMusic();
        m_Paused = true;
    }
    else if (m_Playing && m_Paused)
    {
        Mix_ResumeMusic();
        m_Paused = false;
    }
    else
    {
        return;
    }
}
