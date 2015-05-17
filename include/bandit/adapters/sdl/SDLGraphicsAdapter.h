// Implementation of GraphicsAdapter interface using SDL.

#ifndef SDL_GRAPHICS_ADAPTER_H_
#define SDL_GRAPHICS_ADAPTER_H_

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "bandit/adapters/GraphicsAdapter.h"

class SDLGraphicsAdapter : public GraphicsAdapter
{
  public:
    SDLGraphicsAdapter();
    ~SDLGraphicsAdapter();
    void CreateWindow(std::string title, int width, int height);
    void DestroyWindow();
    void LoadImage(std::string file);
    void UnloadImage();
    bool IsLoaded();
    void RenderImage();

  private:
    void CreateRenderer();
    void DestroyRenderer();

    // SDL window were images will be placed.
    static SDL_Window* window;

    // SDL renderer that renderizes images in the window.
    static SDL_Renderer* renderer;

    // SDL texture, stored in VRAM and processed by GPU.
    SDL_Texture* texture;
};

#endif // SDL_GRAPHICS_ADAPTER_H_