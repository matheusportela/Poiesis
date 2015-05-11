// @file   SoundEffect.h
// @author Matheus Vieira Portela
// @date   10/05/2015
//
// @brief Sound effect playing class.

#ifndef SOUND_EFFECT_H_
#define SOUND_EFFECT_H_

#include <string>

#include <SDL_mixer.h>

// SDL_mixer defines that -1 will keep playing the music
#define PLAY_CONTINUOUSLY -1

// SDL_mixer defines will automatically choose a channel for the value -1.
#define DEFAULT_CHANNEL -1

class SoundEffect
{
  public:
    // Empty constructor.
    SoundEffect();

    // Initializes the music with the given file.
    SoundEffect(std::string file);

    // Opens a music file and stores it in music attribute.
    void Open(std::string file);

    // Checks whether a music has been loaded.
    bool IsOpen() const;

    // Plays the initialized music for the determined number of times. Only a
    // single music can be played at a time.
    void Play(int times = PLAY_CONTINUOUSLY);

    // Stops playing the music.
    void Stop();

  private:
    // SoundEffect that will be played.
    Mix_Chunk* soundEffect;

    // Channel number for the sound effect to be played.
    int channel;
};

#endif // MUSIC_H_