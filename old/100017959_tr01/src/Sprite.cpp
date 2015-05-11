// @file   Sprite.cpp
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Sprite class implementation

#include "Sprite.h"

Sprite::Sprite()
{
    texture = NULL;
}

Sprite::Sprite(std::string file) : Sprite()
{
    Open(file);
}

Sprite::~Sprite()
{
    Close();
}

int Sprite::GetWidth()
{
    return width;
}

int Sprite::GetHeight()
{
    return height;
}

void Sprite::Open(std::string file)
{
    Close();

    texture = IMG_LoadTexture(Game::GetInstance()->GetRenderer(), file.c_str());

    if (!texture)
    {
        std::cerr << "ERROR [Sprite] Could not load texture." << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        exit(1);
    }

    // Get image width and height
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SetClip(0, 0, width, height);
}

void Sprite::Close()
{
    if (IsOpen())
        SDL_DestroyTexture(texture);
}

bool Sprite::IsOpen()
{
    return (texture != NULL);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clippingRectangle.x = x;
    clippingRectangle.y = y;
    clippingRectangle.w = w;
    clippingRectangle.h = h;
}

void Sprite::Render(int x, int y)
{
    SDL_Rect dstRect
    {
        .x = x,
        .y = y,
        .w = clippingRectangle.w,
        .h = clippingRectangle.h
    };
    SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture,
                   &clippingRectangle, &dstRect);
}