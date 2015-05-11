// @file   Text.cpp
// @author Matheus Vieira Portela
// @date   10/05/2015
//
// @brief Display text on screen.

#include "Text.h"

Text::Text(std::string file, int fontSize, TextStyle style, std::string text,
    SDL_Color color, Point position)
{
    color =
    {
        .r = 0,
        .g = 0,
        .b = 0,
        .a = 0
    };
}