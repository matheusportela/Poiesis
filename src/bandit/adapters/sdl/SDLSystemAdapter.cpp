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
    InitializeAudioSystem();
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
        std::cerr << "[SDLSystemAdapter] Could not initialize SDL image. "
            << SDL_GetError() << std::endl;
        exit(1);
    }

    if (TTF_Init() != 0)
    {
        std::cerr << "[Game] Could not initialize SDL text library. "
            << SDL_GetError();
        exit(1);
    }
}

void SDLSystemAdapter::InitializeAudioSystem()
{
    int chunkSize = 1024;
    int flags = MIX_INIT_MP3 | MIX_INIT_OGG;

    // Initializes only JPG loader. Returns zero when no loader could be loaded.
    if (Mix_Init(flags) != flags)
    {
        std::cerr << "[SDLSystemAdapter] Could not initialize SDL mixer library. "
            << SDL_GetError() << std::endl;
        exit(1);
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
        MIX_DEFAULT_CHANNELS, chunkSize) != 0)
    {
        std::cerr << "[SDLSystemAdapter] Could not initialize SDL audio library. "
            << SDL_GetError() << std::endl;
        exit(1);
    }
}

void SDLSystemAdapter::Shutdown()
{
    ShutdownAudioSystem();
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

void SDLSystemAdapter::ShutdownAudioSystem()
{
    Mix_CloseAudio();
    Mix_Quit();
}