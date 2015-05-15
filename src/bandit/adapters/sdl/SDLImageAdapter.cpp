#include "bandit/adapters/sdl/SDLImageAdapter.h"

SDLImageAdapter::SDLImageAdapter() :
    surface(NULL), texture(NULL)
{
}

SDLImageAdapter::~SDLImageAdapter()
{
    Unload();
}

SDL_Surface* SDLImageAdapter::GetSurface()
{
    return surface;
}

SDL_Texture* SDLImageAdapter::GetTexture()
{
    return texture;
}

void SDLImageAdapter::SetTextureAndDestroySurface(SDL_Texture* texture)
{
    this->texture = texture;
    DestroySurface();
}

void SDLImageAdapter::DestroySurface()
{
    if (surface)
        SDL_FreeSurface(surface);
}

void SDLImageAdapter::DestroyTexture()
{
    if (texture)
        SDL_DestroyTexture(texture);
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
    DestroySurface();
    DestroyTexture();
}

bool SDLImageAdapter::IsLoaded()
{
    return (surface != NULL || texture != NULL);
}