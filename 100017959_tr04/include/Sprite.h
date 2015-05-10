// @file   Sprite.h
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Sprite class definition
//
// Definition of class for sprite rendering.

#ifndef SPRITE_H_
#define SPRITE_H_

#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "Point.h"

class Sprite
{
  public:
    // Empty constructor.
    Sprite();

    // Initializes the sprite with a given file.
    Sprite(std::string file);

    // Destroys the sprite.
    virtual ~Sprite() {};

    // Gets image presentation width.
    int GetWidth() const;

    // Gets image presentation height.
    int GetHeight() const;

    // Sets image presentation width.
    void SetWidth(float width);

    // Sets image presentation height.
    void SetHeight(float height);

    // Sets image scalling factor in X axis.
    void SetScaleX(float scale);

    // Sets image scalling factor in Y axis.
    void SetScaleY(float scale);

    // Sets image scalling factor in both X and Y axis.
    void SetScale(float scale);

    // Opens image file and loads it in memory with the resource manager.
    void Open(std::string file);

    // Checks whether the image is open.
    bool IsOpen() const;

    // Sets clipping rectangle size.
    void SetClip(const Point& point, int w, int h);

    // Render sprite.
    void Render(const Point& point, float angle = 0);

  private:
    // Sprite image to be presented.
    SDL_Texture* texture;

    // Image presentation width.
    int width;

    // Image presentation height.
    int height;

    // Rectangle to render only a image part.
    SDL_Rect clippingRectangle;

    // Scalling factors in X and Y axis.
    float scaleX;
    float scaleY;
};

#endif // SPRITE_H_