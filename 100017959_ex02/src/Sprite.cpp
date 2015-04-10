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
    texture = Resources::GetImage(file);
    Point sprintPoint(0, 0);

    // Get image width and height
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SetClip(sprintPoint, width, height);
}

bool Sprite::IsOpen()
{
    return (texture != NULL);
}

void Sprite::SetClip(Point& point, int w, int h)
{
    clippingRectangle.x = point.GetX();
    clippingRectangle.y = point.GetY();
    clippingRectangle.w = w;
    clippingRectangle.h = h;
}

void Sprite::Render(Point& point)
{
    SDL_Rect dstRect
    {
        .x = (int)point.GetX(),
        .y = (int)point.GetY(),
        .w = clippingRectangle.w,
        .h = clippingRectangle.h
    };
    SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture,
                   &clippingRectangle, &dstRect);
}