#include "bandit/adapters/sdl/SDLWindowAdapter.h"

SDLWindowAdapter::SDLWindowAdapter(std::string title, float width, float height)
    : WindowAdapter(title, width, height), window(NULL), renderer(NULL)
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

    CreateRenderer();
    PaintBlack();
}

void SDLWindowAdapter::PaintBlack()
{
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL,
        SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(window);
}

void SDLWindowAdapter::CreateRenderer()
{
    // The second parameter decides which rendering drivers to use.
    // -1 makes SDL select the best available driver.
    // SDL_RENDERER_ACCELERATED enables OpenGL or Direct3D usage.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        std::cerr << "[SDLWindowAdapter] Could not create renderer. "
            << SDL_GetError() << std::endl;
        exit(1);
    }
}

void SDLWindowAdapter::DestroyWindow()
{
    if (window)
        SDL_DestroyWindow(window);

    DestroyRenderer();
}

void SDLWindowAdapter::DestroyRenderer()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
}