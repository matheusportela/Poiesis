// Interface to audio related methods.

#ifndef AUDIO_ADAPTER_H_
#define AUDIO_ADAPTER_H_

#include <string>

class AudioAdapter
{
  public:
    virtual ~AudioAdapter() {}

    // Loads an audio file from a specified file to the memory.
    virtual void Load(std::string file) = 0;

    // Unloads a previously loaded audio from memory.
    virtual void Unload(std::string file) = 0;

    // Checks whether an audio has been loaded with this instance.
    virtual bool IsLoaded(std::string file) = 0;

    // Plays currently loaded audio.
    virtual void Play(std::string file, int repetitions = 0) = 0;

    // Stops playing audio.
    virtual void Stop(std::string file) = 0;
};

#endif // AUDIO_ADAPTER_H_