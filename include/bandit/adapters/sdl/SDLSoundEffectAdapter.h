// Implementation of AudioAdapter interface using SDL.
// This adapter is designed to play sound effects: short audio streams that can
// overlap with other sound effects.

#ifndef SDL_SOUND_EFFECT_ADAPTER_H_
#define SDL_SOUND_EFFECT_ADAPTER_H_

#include <iostream>

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
    SDLSoundEffectAdapter();
    ~SDLSoundEffectAdapter();
    void Load(std::string file);
    void Unload();
    bool IsLoaded();
    void Play(int repetitions);
    void Stop();

  private:
    // SoundEffect that will be played.
    Mix_Chunk* soundEffect;

    // Channel number for the sound effect to be played.
    int channel;
};

#endif // SDL_SOUND_EFFECT_ADAPTER_H_