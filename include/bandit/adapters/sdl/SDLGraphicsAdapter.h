// Implementation of GraphicsAdapter interface using SDL.

#ifndef SDL_GRAPHICS_ADAPTER_H_
#define SDL_GRAPHICS_ADAPTER_H_

#include <iostream>
#include <unordered_map>

#include <SDL.h>
#include <SDL_image.h>

#include "bandit/adapters/GraphicsAdapter.h"

class SDLGraphicsAdapter : public GraphicsAdapter
{
  public:
    ~SDLGraphicsAdapter();
    void CreateWindow(std::string title, int width, int height);
    void DestroyWindow();
    void LoadImage(std::string file);
    void UnloadImage(std::string file);
    bool IsLoaded(std::string file);
    void RenderImage(std::string file);

  private:
    void CreateRenderer();
    void DestroyRenderer();
    void UnloadAllTextures();

    // SDL window were images will be placed.
    static SDL_Window* window;

    // SDL renderer that renderizes images in the window.
    static SDL_Renderer* renderer;

    // Table to provide reusage of loaded textures.
    static std::unordered_map<std::string, SDL_Texture*> texturesTable;
};

#endif // SDL_GRAPHICS_ADAPTER_H_