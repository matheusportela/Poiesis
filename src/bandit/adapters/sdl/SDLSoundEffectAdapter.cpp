#include "bandit/adapters/sdl/SDLSoundEffectAdapter.h"

SDLSoundEffectAdapter::SDLSoundEffectAdapter() :
    soundEffect(NULL), channel(EMPTY_CHANNEL)
{
}

SDLSoundEffectAdapter::~SDLSoundEffectAdapter()
{
    Unload();
}

void SDLSoundEffectAdapter::Load(std::string file)
{
    soundEffect = Mix_LoadWAV(file.c_str());

    if (!soundEffect)
    {
        std::cerr << "[SDLSoundEffectAdapter] Could not load sound effect \""
            << file << "\". " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void SDLSoundEffectAdapter::Unload()
{
    if (IsLoaded())
        Mix_FreeChunk(soundEffect);
}

bool SDLSoundEffectAdapter::IsLoaded()
{
    return (soundEffect != NULL);
}

void SDLSoundEffectAdapter::Play(int repetitions)
{
    if (!soundEffect)
    {
        std::cerr << "[SDLSoundEffectAdapter] Cannot play sound effect without "
            << "loading it first." << std::endl;
        exit(1);
    }

    channel = Mix_PlayChannel(DEFAULT_CHANNEL, soundEffect, repetitions);
}

void SDLSoundEffectAdapter::Stop()
{
    if (channel == EMPTY_CHANNEL)
    {
        std::cerr << "[SDLSoundEffectAdapter] Cannot stop sound effect without "
            << "playing it first." << std::endl;
        exit(1);
    }

    Mix_HaltChannel(channel);
    channel = EMPTY_CHANNEL;
}