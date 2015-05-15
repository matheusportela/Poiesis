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
    SDL_Surface* GetSurface();
    SDL_Texture* GetTexture();
    void SetTextureAndDestroySurface(SDL_Texture* texture);
    void DestroySurface();
    void DestroyTexture();
    void Load(std::string file);
    void Unload();
    bool IsLoaded();

  private:
    // SDL surface representing an image.
    SDL_Surface* surface;

    // SDL texture, stored in VRAM and processed by GPU.
    SDL_Texture* texture;
};

#endif // SDL_IMAGE_ADAPTER_H_