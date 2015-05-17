#include "bandit/adapters/sdl/SDLSoundEffectAdapter.h"

std::unordered_map<std::string, Mix_Chunk*> SDLSoundEffectAdapter::audioTable;
std::unordered_map<std::string, int> SDLSoundEffectAdapter::channelTable;

SDLSoundEffectAdapter::~SDLSoundEffectAdapter()
{
    UnloadAllSoundEffects();
}

void SDLSoundEffectAdapter::Load(std::string file)
{
    Mix_Chunk* soundEffect = Mix_LoadWAV(file.c_str());

    if (!soundEffect)
    {
        std::cerr << "[SDLSoundEffectAdapter] Could not load sound effect \""
            << file << "\". " << SDL_GetError() << std::endl;
        exit(1);
    }

    audioTable[file] = soundEffect;
    channelTable[file] = EMPTY_CHANNEL;
}

void SDLSoundEffectAdapter::Unload(std::string file)
{
    if (IsLoaded(file))
    {
        Mix_FreeChunk(audioTable[file]);
        audioTable.erase(file);
        channelTable.erase(file);
    }
}

void SDLSoundEffectAdapter::UnloadAllSoundEffects()
{
    for (auto fileAndSoundEffect : audioTable)
        Unload(fileAndSoundEffect.first);
}

bool SDLSoundEffectAdapter::IsLoaded(std::string file)
{
    return (audioTable.find(file) != audioTable.end());
}

void SDLSoundEffectAdapter::Play(std::string file, int repetitions)
{
    if (!IsLoaded(file))
    {
        std::cerr << "[SDLSoundEffectAdapter] Cannot play sound effect without "
            << "loading it first." << std::endl;
        exit(1);
    }

    int channel = Mix_PlayChannel(DEFAULT_CHANNEL, audioTable[file], repetitions);
    channelTable[file] = channel;
}

void SDLSoundEffectAdapter::Stop(std::string file)
{
    if (!IsLoaded(file))
    {
        std::cerr << "[SDLSoundEffectAdapter] Cannot stop sound effect without "
            << "loading it first." << std::endl;
        exit(1);
    }

    if (channelTable[file] == EMPTY_CHANNEL)
    {
        std::cerr << "[SDLSoundEffectAdapter] Cannot stop sound effect without "
            << "playing it first." << std::endl;
        exit(1);
    }

    Mix_HaltChannel(channelTable[file]);
    channelTable[file] = EMPTY_CHANNEL;
}