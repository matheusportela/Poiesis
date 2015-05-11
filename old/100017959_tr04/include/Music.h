// @file   Music.h
// @author Matheus Vieira Portela
// @date   10/05/2015
//
// @brief Music playing class.

#ifndef MUSIC_H_
#define MUSIC_H_

#include <string>

#include <SDL_mixer.h>

// SDL_mixer defines that -1 will keep playing the music
#define PLAY_CONTINUOUSLY -1

// Time, in ms, to fade out the current music being played.
#define FADE_OUT_TIME 10

class Music
{
  public:
    // Empty constructor.
    Music();

    // Initializes the music with the given file.
    Music(std::string file);

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
    // Music that will be played.
    Mix_Music* music;
};

#endif // MUSIC_H_