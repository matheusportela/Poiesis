// Implementation of AudioAdapter interface using SDL.
// This adapter is designed to play background music. Due to SDL limitations,
// only a single music can be played a time.

#ifndef SDL_MUSIC_ADAPTER_H_
#define SDL_MUSIC_ADAPTER_H_

#include <iostream>
#include <unordered_map>

#include <SDL_mixer.h>

#include "bandit/adapters/AudioAdapter.h"

// Repeat the sound effect forever.
#define REPEAT_CONTINUOUSLY -1

// Time, in ms, to fade out the current music being played.
#define FADE_OUT_TIME 10

class SDLMusicAdapter : public AudioAdapter
{
  public:
    ~SDLMusicAdapter();
    void Load(std::string file);
    void Unload(std::string file);
    bool IsLoaded(std::string file);
    void Play(std::string file, int repetitions = REPEAT_CONTINUOUSLY);
    void Stop(std::string file);

  private:
    void UnloadAllMusics();

    // Storage for all loaded musics.
    static std::unordered_map<std::string, Mix_Music*> musicsTable;
};

#endif // SDL_MUSIC_ADAPTER_H_