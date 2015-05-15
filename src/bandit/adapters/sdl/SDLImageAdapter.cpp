#include "bandit/adapters/sdl/SDLImageAdapter.h"

SDLImageAdapter::SDLImageAdapter() :
    surface(NULL)
{
}

SDLImageAdapter::~SDLImageAdapter()
{
    Unload();
}

void SDLImageAdapter::Load(std::string file)
{
    surface = IMG_Load(file.c_str());

    if (!surface)
    {
        std::cerr << "[SDLImageAdapter] Could not load image \"" << file
            << "\". " << SDL_GetError();
        exit(1);
    }
}

void SDLImageAdapter::Unload()
{
    if (IsLoaded())
        SDL_FreeSurface(surface);
}

bool SDLImageAdapter::IsLoaded()
{
    return (surface != NULL);
}