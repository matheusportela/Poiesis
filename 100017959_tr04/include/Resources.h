// @file   Resources.h
// @author Matheus Vieira Portela
// @date   10/04/2015
//
// @brief Resource manager
//
// Resource manager is responsible to allocate a single image on memory and
// reuse it whenever necessary. It also provides desallocation functionalities.

#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <string>
#include <unordered_map>

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Game.h"
#include "Logger.h"

class Resources
{
  public:
    // Checks whether an image is loaded in memory.
    static bool HasImage(std::string file);

    // Loads an image into memory.
    static SDL_Texture* LoadImage(std::string file);

    // Get an SDL texture from memory, if present, or load it from the given
    // file.
    static SDL_Texture* GetImage(std::string file);

    // Remove images from memory.
    static void ClearImages();

    // Checks whether a music is loaded in memory.
    static bool HasMusic(std::string file);

    // Loads a music into memory.
    static Mix_Music* LoadMusic(std::string file);

    // Get an SDL music from memory, if present, or load it from the given
    // file.
    static Mix_Music* GetMusic(std::string file);

    // Remove musics from memory.
    static void ClearMusics();

    // Checks whether a sound effect is loaded in memory.
    static bool HasSoundEffect(std::string file);

    // Loads a sound effect into memory.
    static Mix_Chunk* LoadSoundEffect(std::string file);

    // Get an SDL sound effect from memory, if present, or load it from the given
    // file.
    static Mix_Chunk* GetSoundEffect(std::string file);

    // Remove sound effects from memory.
    static void ClearSoundEffects();

    // Checks whether a font is loaded in memory.
    static bool HasFont(std::string file);

    // Loads a font into memory.
    static TTF_Font* LoadFont(std::string file, int size);

    // Get an SDL font from memory, if present, or load it from the given
    // file and size in the format "file size".
    static TTF_Font* GetFont(std::string file, int size);

    // Remove fonts from memory.
    static void ClearFonts();


  private:
    // Generates the key used to store a font.
    static std::string GenerateFontKey(std::string file, int size);
    
    static std::unordered_map<std::string, SDL_Texture*> imageTable;
    static std::unordered_map<std::string, Mix_Music*> musicTable;
    static std::unordered_map<std::string, Mix_Chunk*> soundEffectTable;
    static std::unordered_map<std::string, TTF_Font*> fontTable;
};

#endif // RESOURCES_H_