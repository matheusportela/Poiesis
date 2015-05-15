// Implementation of WindowAdapter interface using SDL.

#ifndef SDL_WINDOW_ADAPTER_H_
#define SDL_WINDOW_ADAPTER_H_

#include <iostream>

#include <SDL.h>

#include "bandit/adapters/WindowAdapter.h"
#include "bandit/adapters/ImageAdapter.h"
#include "bandit/adapters/sdl/SDLImageAdapter.h"

class SDLWindowAdapter : public WindowAdapter
{
  public:
    SDLWindowAdapter(std::string title, float width, float height);
    ~SDLWindowAdapter();
    void CreateWindow();
    void DestroyWindow();

  private:
    void PaintBlack();
    void CreateRenderer();
    void DestroyRenderer();

    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif // SDL_WINDOW_ADAPTER_H_