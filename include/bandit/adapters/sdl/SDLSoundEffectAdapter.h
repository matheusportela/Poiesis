// Implementation of AudioAdapter interface using SDL.
// This adapter is designed to play sound effects: short audio streams that can
// overlap with other sound effects.

#ifndef SDL_SOUND_EFFECT_ADAPTER_H_
#define SDL_SOUND_EFFECT_ADAPTER_H_

#include <iostream>
#include <unordered_map>

#include <SDL_mixer.h>

#include "bandit/adapters/AudioAdapter.h"

// SDL defines which channel to use.
#define DEFAULT_CHANNEL -1

// No channel was allocated to the sound effect yet.
#define EMPTY_CHANNEL -2

// Repeat the sound effect forever.
#define REPEAT_CONTINUOUSLY -1

class SDLSoundEffectAdapter : public AudioAdapter
{
  public:
    ~SDLSoundEffectAdapter();
    void Load(std::string file);
    void Unload(std::string file);
    bool IsLoaded(std::string file);
    void Play(std::string file, int repetitions);
    void Stop(std::string file);

  private:
    void UnloadAllSoundEffects();

    // Sound effect that are loaded.
    static std::unordered_map<std::string, Mix_Chunk*> audioTable;

    // Channel number for sound effects.
    static std::unordered_map<std::string, int> channelTable;
};

#endif // SDL_SOUND_EFFECT_ADAPTER_H_