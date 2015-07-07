#include "bandit/adapters/sdl/SDLGraphicsAdapter.h"

SDL_Window* SDLGraphicsAdapter::window = NULL;
SDL_Renderer* SDLGraphicsAdapter::renderer = NULL;
std::unordered_map<std::string, SDL_Texture*> SDLGraphicsAdapter::texturesTable;
std::unordered_map<std::string, SDLGraphicsAdapter::TextureSettings> SDLGraphicsAdapter::texturesSettings;
std::unordered_map<std::string, TTF_Font*> SDLGraphicsAdapter::fontTable;
std::vector<SDLGraphicsAdapter::TextSettings> SDLGraphicsAdapter::textSettings;
std::vector<SDL_Texture*> SDLGraphicsAdapter::textTextures;

SDLGraphicsAdapter::~SDLGraphicsAdapter()
{
    UnloadAllTextures();
    UnloadAllFonts();
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
        .height = 0
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

void SDLGraphicsAdapter::LoadFont(std::string fontFile, int size)
{
    TTF_Font* font = TTF_OpenFont(fontFile.c_str(), size);

    if (!font)
    {
        std::cerr << "[SDLGraphicsAdapter] Could not load font \"" << fontFile
            << "\". " << SDL_GetError();
        exit(1);
    }

    fontTable[fontFile] = font;
}

void SDLGraphicsAdapter::UnloadFont(std::string fontFile)
{
    if (IsFontLoaded(fontFile))
    {
        TTF_CloseFont(fontTable[fontFile]);
        fontTable.erase(fontFile);
    }
}

bool SDLGraphicsAdapter::IsFontLoaded(std::string fontFile)
{
    return (fontTable.find(fontFile) != fontTable.end());
}

void SDLGraphicsAdapter::UnloadAllFonts()
{
    TTF_Font* font;
    std::unordered_map<std::string, TTF_Font*>::iterator it;

    while (fontTable.size() != 0)
    {
        it = fontTable.begin();
        font = it->second;
        TTF_CloseFont(font);
        fontTable.erase(it->first);
    }
}

void SDLGraphicsAdapter::InitRendering()
{
    // Select the black color for drawing.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Clear the entire screen with the selected color.
    SDL_RenderClear(renderer);

}

void SDLGraphicsAdapter::RenderImage(std::string file, int x, int y,
    float rotation, float scale, int currentFrame, int numFrames)
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
        .x = settings.width*currentFrame/numFrames,
        .y = 0,
        .w = settings.width/numFrames,
        .h = settings.height
    };
    SDL_Rect dstRect
    {
        .x = x,
        .y = y,
        .w = (int)(clipRect.w*scale),
        .h = (int)(clipRect.h*scale)
    };

    // Moves texture to proper GPU memory location.
    // Third argument deals with clipping the image. NULL makes it stretch to
    // fill the window.
    // Fourth argument deals with displaying the image in the proper position.
    // NULL makes it show at the current window position.
    // Fifth argument deals with rotating the sprite an amount of degrees.
    // Since the entire project uses international units, the given rotation is
    // in radians and must be converted.
    SDL_RenderCopyEx(renderer, texture, &clipRect, &dstRect, rotation*180.0/M_PI, NULL,
        SDL_FLIP_NONE);
}

void SDLGraphicsAdapter::RenderCenteredImage(std::string file, int x, int y,
    float rotation, float scale, int currentFrame, int numFrames)
{
    if (!IsLoaded(file))
    {
        std::cerr << "[SDLGraphicsAdapter] Cannot render image without loading "
            << "it first." << std::endl;
        exit(1);
    }

    TextureSettings settings = texturesSettings[file];

    RenderImage(file, x - scale*settings.width/(2*numFrames), y - scale*settings.height/2,
        rotation, scale, currentFrame, numFrames);
}

void SDLGraphicsAdapter::Write(std::string text, std::string fontFile, int x, int y)
{
    int width;
    int height;
    SDL_Color color =
    {
        .r = 255,
        .g = 255,
        .b = 255,
        .a = 0      
    };
    TTF_Font* font = fontTable[fontFile];
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    TextSettings settings =
    {
        .x = x,
        .y = y,
        .width = width,
        .height = height
    };

    textSettings.push_back(settings);
    textTextures.push_back(texture);
}

void SDLGraphicsAdapter::RenderTexts()
{
    SDL_Texture* texture;
    TextSettings settings;
    SDL_Rect clipRect;
    SDL_Rect dstRect;

    for (unsigned int i = 0; i < textTextures.size(); ++i)
    {
        texture = textTextures[i];
        settings = textSettings[i];
        clipRect =
        {
            .x = 0,
            .y = 0,
            .w = settings.width,
            .h = settings.height
        };
        dstRect =
        {
            .x = settings.x,
            .y = settings.y,
            .w = settings.width,
            .h = settings.height
        };
        SDL_RenderCopy(renderer, texture, &clipRect, &dstRect);
        SDL_DestroyTexture(texture);
    }

    textTextures.clear();
    textSettings.clear();
}

void SDLGraphicsAdapter::FinishRendering()
{
    RenderTexts();

    // Forces rendering images at the GPU.
    SDL_RenderPresent(renderer);
}