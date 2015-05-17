#include "bandit/adapters/sdl/SDLMusicAdapter.h"

SDLMusicAdapter::SDLMusicAdapter() :
    music(NULL)
{
}

SDLMusicAdapter::~SDLMusicAdapter()
{
    Unload();
}

void SDLMusicAdapter::Load(std::string file)
{
    music = Mix_LoadMUS(file.c_str());

    if (!music)
    {
        std::cerr << "[SDLMusicAdapter] Could not load music file \"" << file
            << "\". " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void SDLMusicAdapter::Unload()
{
    if (IsLoaded())
        Mix_FreeMusic(music);
}

bool SDLMusicAdapter::IsLoaded()
{
    return (music != NULL);
}

void SDLMusicAdapter::Play(int repetitions)
{
    if (!music)
    {
        std::cerr << "[SDLMusicAdapter] Cannot play music without loading it "
            << "first." << std::endl;
        exit(1);
    }

    Mix_PlayMusic(music, repetitions);
}

void SDLMusicAdapter::Stop()
{
    Mix_FadeOutMusic(FADE_OUT_TIME);
}