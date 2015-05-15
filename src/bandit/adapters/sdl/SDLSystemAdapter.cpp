#include "bandit/adapters/sdl/SDLSystemAdapter.h"

SDLSystemAdapter::SDLSystemAdapter()
{
}

SDLSystemAdapter::~SDLSystemAdapter()
{
}

void SDLSystemAdapter::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        std::cerr << "[SDLSystemAdapter] Could not initialize SDL systems. "
            << SDL_GetError();
        exit(1);
    }
}

void SDLSystemAdapter::Shutdown()
{
    SDL_Quit();
}