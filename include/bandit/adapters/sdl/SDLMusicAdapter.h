// Implementation of AudioAdapter interface using SDL.
// This adapter is designed to play background music. Due to SDL limitations,
// only a single music can be played a time.

#ifndef SDL_MUSIC_ADAPTER_H_
#define SDL_MUSIC_ADAPTER_H_

#include <iostream>

#include <SDL_mixer.h>

#include "bandit/adapters/AudioAdapter.h"

// Repeat the sound effect forever.
#define REPEAT_CONTINUOUSLY -1

// Time, in ms, to fade out the current music being played.
#define FADE_OUT_TIME 10

class SDLMusicAdapter : public AudioAdapter
{
  public:
    SDLMusicAdapter();
    ~SDLMusicAdapter();
    void Load(std::string file);
    void Unload();
    bool IsLoaded();
    void Play(int repetitions = REPEAT_CONTINUOUSLY);
    void Stop();

  private:
    // Music that will be played.
    Mix_Music* music;
};

#endif // SDL_MUSIC_ADAPTER_H_