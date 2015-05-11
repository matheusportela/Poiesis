// @file   Sprite.h
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Sprite class definition
//
// Definition of class for sprite rendering.

#ifndef SPRITE_H_
#define SPRITE_H_

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"

// Forward declaration to avoid circular include.
class Game;

class Sprite
{
  public:
    // Empty constructor.
    Sprite();

    // Initializes the sprite with a given file.
    Sprite(std::string file);

    // Destroys the sprite.
    ~Sprite();

    // Gets image presentation width.
    int GetWidth();

    // Gets image presentation height.
    int GetHeight();

    // Opens image file.
    void Open(std::string file);

    // Close an opened image.
    void Close();

    // Checks whether the image is open.
    bool IsOpen();

    // Sets clipping rectangle size.
    void SetClip(int x, int y, int w, int h);

    // Render sprite.
    void Render(int x, int y);

  private:
    // Sprite image to be presented.
    SDL_Texture* texture;

    // Image presentation width.
    int width;

    // Image presentation height.
    int height;

    // Rectangle to render only a image part.
    SDL_Rect clippingRectangle;
};

#endif // SPRITE_H_