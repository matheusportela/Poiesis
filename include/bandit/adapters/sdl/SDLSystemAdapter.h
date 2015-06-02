// Implementation of SDL initialization and shutdown.

#ifndef SDL_SYSTEM_ADAPTER_H_
#define SDL_SYSTEM_ADAPTER_H_

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "bandit/adapters/SystemAdapter.h"

class SDLSystemAdapter : public SystemAdapter
{
  public:
    SDLSystemAdapter();
    ~SDLSystemAdapter();
    void Initialize();
    void Shutdown();
    
  private:
    void InitializeSDL();
    void InitializeImageSystem();
    void InitializeAudioSystem();
    void ShutdownSDL();
    void ShutdownImageSystem();
    void ShutdownAudioSystem();
};

#endif // SDL_SYSTEM_ADAPTER_H_