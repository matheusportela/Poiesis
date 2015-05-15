#include "bandit/adapters/sdl/SDLSystemAdapter.h"

SDLSystemAdapter::SDLSystemAdapter()
{
}

SDLSystemAdapter::~SDLSystemAdapter()
{
}

void SDLSystemAdapter::Initialize()
{
    InitializeSDL();
    InitializeImageSystem();
}

void SDLSystemAdapter::InitializeSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        std::cerr << "[SDLSystemAdapter] Could not initialize SDL systems. "
            << SDL_GetError() << std::endl;
        exit(1);
    }
}

void SDLSystemAdapter::InitializeImageSystem()
{
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
    {
        std::cerr << "[Game] Could not initialize SDL image. "
            << SDL_GetError() << std::endl;
        exit(1);
    }
}

void SDLSystemAdapter::Shutdown()
{
    ShutdownImageSystem();
    ShutdownSDL();
}

void SDLSystemAdapter::ShutdownSDL()
{
    SDL_Quit();
}

void SDLSystemAdapter::ShutdownImageSystem()
{
    IMG_Quit();
}
