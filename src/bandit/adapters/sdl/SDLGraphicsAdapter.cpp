#include "bandit/adapters/sdl/SDLGraphicsAdapter.h"

SDL_Window* SDLGraphicsAdapter::window = NULL;
SDL_Renderer* SDLGraphicsAdapter::renderer = NULL;

SDLGraphicsAdapter::SDLGraphicsAdapter() :
    texture(NULL)
{
}

SDLGraphicsAdapter::~SDLGraphicsAdapter()
{
    UnloadImage();
}

void SDLGraphicsAdapter::CreateWindow(std::string title, int width, int height)
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
}

void SDLGraphicsAdapter::CreateRenderer()
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

void SDLGraphicsAdapter::DestroyWindow()
{
    DestroyRenderer();

    if (window)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }
}

void SDLGraphicsAdapter::DestroyRenderer()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
}

void SDLGraphicsAdapter::LoadImage(std::string file)
{
    if (!renderer)
    {
        std::cerr << "[SDLGraphicsAdapter] Cannot load image without a window"
            << std::endl;
        exit(1);
    }

    texture = IMG_LoadTexture(renderer, file.c_str());

    if (!texture)
    {
        std::cerr << "[SDLGraphicsAdapter] Could not load image \"" << file
            << "\". " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void SDLGraphicsAdapter::UnloadImage()
{
    if (IsLoaded())
        SDL_DestroyTexture(texture);
}

bool SDLGraphicsAdapter::IsLoaded()
{
    return (texture != NULL);
}

void SDLGraphicsAdapter::RenderImage()
{
    if (!texture)
    {
        std::cerr << "[SDLGraphicsAdapter] Cannot render image without loading "
            << "it first." << std::endl;
        exit(1);
    }

    // Moves texture to proper GPU memory location.
    // Third argument deals with clipping the image. NULL makes it stretch to
    // fill the window.
    // Fourth argument deals with displaying the image in the proper position.
    // NULL makes it show at the current window position.
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Forces rendering the image.
    SDL_RenderPresent(renderer);
}