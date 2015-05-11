// @file   Text.cpp
// @author Matheus Vieira Portela
// @date   10/05/2015
//
// @brief Display text on screen.

#include "Text.h"
#include "Game.h"
#include "Resources.h"

SDL_Color Text::White =
{
    .r = 255,
    .g = 255,
    .b = 255,
    .a = 0
};

SDL_Color Text::Black =
{
    .r = 0,
    .g = 0,
    .b = 0,
    .a = 0
};

Text::Text(std::string file, int fontSize, TextStyle style, std::string text,
    SDL_Color color, Point position) : fontSize(fontSize), style(style),
    text(text), color(color), texture(NULL)
{
    font = Resources::GetFont(file, fontSize);
    RemakeTexture();
    SetCenter(position);
    LOG_D("Text box: " << box.ToString());
}

Text::~Text()
{
    if (texture)
        SDL_DestroyTexture(texture);
}

void Text::SetPosition(Point position)
{
    box.SetPoint(position);
}

void Text::SetCenter(Point position)
{
    box.SetCenter(position);
}

void Text::Render()
{
    Point position = box.GetPoint();
    SDL_Rect clipRect =
    {
        .x = 0,
        .y = 0,
        .w = (int)box.GetW(),
        .h = (int)box.GetH()
    };

    SDL_Rect dstRect =
    {
        .x = (int)position.GetX(),
        .y = (int)position.GetY(),
        .w = (int)box.GetW(),
        .h = (int)box.GetH()
    };

    SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture,
                   &clipRect, &dstRect);
}

void Text::RemakeTexture()
{
    int width;
    int height;
    SDL_Surface* surface;
    SDL_Color backgroundColor = Black;

    if (texture)
        SDL_DestroyTexture(texture);;

    switch (style)
    {
        case Solid:
            surface = TTF_RenderText_Solid(font, text.c_str(), color);
            break;
        case Shaded:
            surface = TTF_RenderText_Shaded(font, text.c_str(), color,
                backgroundColor);
            break;
        case Blended:
            surface = TTF_RenderText_Blended(font, text.c_str(), color);
            break;
    }

    texture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(),
        surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    box.SetW(width);
    box.SetH(height);
    LOG_D("Text size: " << width << " " << height);
}