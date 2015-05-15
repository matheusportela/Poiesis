#include "bandit/adapters/sdl/SDLWindowAdapter.h"

SDLWindowAdapter::SDLWindowAdapter(std::string title, float width, float height)
    : WindowAdapter(title, width, height)
{
}

SDLWindowAdapter::~SDLWindowAdapter()
{
    DestroyWindow();
}

void SDLWindowAdapter::CreateWindow()
{
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height, 0);

    if (!window)
    {
        std::cerr << "[SDLWindowAdapter] Could not create window. "
            << SDL_GetError() << std::endl;
        exit(1);
    }
}

void SDLWindowAdapter::DestroyWindow()
{
    if (window)
        SDL_DestroyWindow(window);
}