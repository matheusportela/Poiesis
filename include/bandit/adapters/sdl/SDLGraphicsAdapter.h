// Implementation of GraphicsAdapter interface using SDL.

#ifndef SDL_GRAPHICS_ADAPTER_H_
#define SDL_GRAPHICS_ADAPTER_H_

#include <iostream>
#include <unordered_map>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "bandit/adapters/GraphicsAdapter.h"

class SDLGraphicsAdapter : public GraphicsAdapter
{
  public:
    ~SDLGraphicsAdapter();
    void CreateWindow(std::string title, int width, int height);
    void DestroyWindow();
    void LoadImage(std::string file);
    void UnloadImage(std::string file);
    bool IsLoaded(std::string file);

    // Only one font size can be loaded at a time.
    void LoadFont(std::string fontFile, int size);
    void UnloadFont(std::string fontFile);
    bool IsFontLoaded(std::string fontFile);
    void InitRendering();
    void RenderImage(std::string file, int x, int y, float scale);
    void RenderCenteredImage(std::string file, int x, int y, float scale);
    void Write(std::string text, std::string fontFile, int x, int y);
    void FinishRendering();

  private:
    struct TextureSettings
    {
        int width;
        int height;
    };

    struct TextSettings
    {
        int x;
        int y;
        int width;
        int height;
    };

    void CreateRenderer();
    void DestroyRenderer();
    void LoadTexture(std::string file);
    void UpdateTextureSettings(std::string file);
    void UnloadAllTextures();
    void UnloadAllFonts();
    void RenderTexts();

    // SDL window were images will be placed.
    static SDL_Window* window;

    // SDL renderer that renderizes images in the window.
    static SDL_Renderer* renderer;

    // Table to provide reusage of loaded textures.
    static std::unordered_map<std::string, SDL_Texture*> texturesTable;

    // Table to maintain the image dimensions settings.
    static std::unordered_map<std::string, TextureSettings> texturesSettings;

    // Table to provide reusage of loaded fonts.
    static std::unordered_map<std::string, TTF_Font*> fontTable;

    // Table to maintain the text dimensions and positioning settings.
    static std::vector<TextSettings> textSettings;

    // Table to store texts in a rendering cycle.
    static std::vector<SDL_Texture*> textTextures;
};

#endif // SDL_GRAPHICS_ADAPTER_H_