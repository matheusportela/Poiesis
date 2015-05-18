#include "bandit/adapters/sdl/SDLGraphicsAdapter.h"

SDL_Window* SDLGraphicsAdapter::window = NULL;
SDL_Renderer* SDLGraphicsAdapter::renderer = NULL;
std::unordered_map<std::string, SDL_Texture*> SDLGraphicsAdapter::texturesTable;
std::unordered_map<std::string, SDLGraphicsAdapter::TextureSettings> SDLGraphicsAdapter::texturesSettings;

SDLGraphicsAdapter::~SDLGraphicsAdapter()
{
    UnloadAllTextures();
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

    LoadTexture(file);
    UpdateTextureSettings(file);
}

void SDLGraphicsAdapter::LoadTexture(std::string file)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());

    if (!texture)
    {
        std::cerr << "[SDLGraphicsAdapter] Could not load image \"" << file
            << "\". " << SDL_GetError() << std::endl;
        exit(1);
    }

    texturesTable[file] = texture;
}

void SDLGraphicsAdapter::UpdateTextureSettings(std::string file)
{
    TextureSettings settings =
    {
        .width = 0,
        .height = 0,
        .scale = 1
    };

    SDL_QueryTexture(texturesTable[file], NULL, NULL, &settings.width,
        &settings.height);

    texturesSettings[file] = settings;
}

void SDLGraphicsAdapter::UnloadImage(std::string file)
{
    if (IsLoaded(file))
    {
        SDL_DestroyTexture(texturesTable[file]);
        texturesTable.erase(file);
    }
}

void SDLGraphicsAdapter::UnloadAllTextures()
{
    SDL_Texture* texture;
    std::unordered_map<std::string, SDL_Texture*>::iterator it;

    while (texturesTable.size() != 0)
    {
        it = texturesTable.begin();
        texture = it->second;
        SDL_DestroyTexture(texture);
        texturesTable.erase(it->first);
    }
}

bool SDLGraphicsAdapter::IsLoaded(std::string file)
{
    return (texturesTable.find(file) != texturesTable.end());
}

void SDLGraphicsAdapter::RenderImage(std::string file, int x, int y)
{
    if (!IsLoaded(file))
    {
        std::cerr << "[SDLGraphicsAdapter] Cannot render image without loading "
            << "it first." << std::endl;
        exit(1);
    }

    SDL_Texture* texture = texturesTable[file];
    TextureSettings settings = texturesSettings[file];
    SDL_Rect clipRect
    {
        .x = 0,
        .y = 0,
        .w = settings.width,
        .h = settings.height
    };
    SDL_Rect dstRect
    {
        .x = x,
        .y = y,
        .w = settings.width*settings.scale,
        .h = settings.height*settings.scale
    };

    // Moves texture to proper GPU memory location.
    // Third argument deals with clipping the image. NULL makes it stretch to
    // fill the window.
    // Fourth argument deals with displaying the image in the proper position.
    // NULL makes it show at the current window position.
    SDL_RenderCopy(renderer, texture, &clipRect, &dstRect);

    // Forces rendering the image.
    SDL_RenderPresent(renderer);
}

void SDLGraphicsAdapter::SetImageScale(std::string file, int scale)
{
    if (!IsLoaded(file))
    {
        std::cerr << "[SDLGraphicsAdapter] Cannot scale image without loading "
            << "it first." << std::endl;
        exit(1);
    }

    texturesSettings[file].scale = scale;
}