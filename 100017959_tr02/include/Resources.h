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

#include <iostream>
#include <string>
#include <unordered_map>

#include <SDL_image.h>

#include "Game.h"

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

  private:
    static std::unordered_map<std::string, SDL_Texture*> imageTable;
};

#endif // RESOURCES_H_