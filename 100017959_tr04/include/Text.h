// @file   Text.h
// @author Matheus Vieira Portela
// @date   10/05/2015
//
// @brief Display text on screen.

#ifndef TEXT_H_
#define TEXT_H_

#include <string>

#include <SDL_ttf.h>

#include "Point.h"
#include "Rect.h"

class Text
{
  public:
    enum TextStyle
    {
        Solid,
        Shaded,
        Blended
    };

    Text(std::string file, int fontSize, TextStyle style, std::string text,
        SDL_Color color, Point position = Point(0, 0));

  private:
    TTF_Font* font;
    int fontSize;
    TextStyle style;
    std::string text;
    SDL_Color color;
    SDL_Texture* texture;
    Rect box;
};

#endif // TEXT_H_