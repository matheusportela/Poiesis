// Implementation of ImageAdapter interface using SDL.

#ifndef SDL_IMAGE_ADAPTER_H_
#define SDL_IMAGE_ADAPTER_H_

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "bandit/adapters/ImageAdapter.h"

class SDLImageAdapter : public ImageAdapter
{
  public:
    SDLImageAdapter();
    ~SDLImageAdapter();
    void Load(std::string file);
    void Unload();
    bool IsLoaded();

  private:
    // SDL surface representing an image.
    SDL_Surface* surface;
};

#endif // SDL_IMAGE_ADAPTER_H_