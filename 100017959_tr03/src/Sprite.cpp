// @file   Sprite.cpp
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Sprite class implementation

#include "Sprite.h"

#include "Game.h"

Sprite::Sprite() : texture(NULL), scaleX(1), scaleY(1)
{
}

Sprite::Sprite(std::string file) : Sprite()
{
    Open(file);
}

int Sprite::GetWidth() const
{
    return width;
}

int Sprite::GetHeight() const
{
    return height;
}

void Sprite::SetWidth(float width)
{
    this->width = width;
}

void Sprite::SetHeight(float height)
{
    this->height = height;
}

void Sprite::SetScaleX(float scale)
{
    scaleX = scale;
}

void Sprite::SetScaleY(float scale)
{
    scaleY = scale;
}

void Sprite::SetScale(float scale)
{
    scaleX = scale;
    scaleY = scale;
}

void Sprite::Open(std::string file)
{
    texture = Resources::GetImage(file);
    Point sprintPoint(0, 0);

    // Get image width and height
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SetClip(sprintPoint, width, height);
}

bool Sprite::IsOpen() const
{
    return (texture != NULL);
}

void Sprite::SetClip(const Point& point, int w, int h)
{
    clippingRectangle.x = point.GetX();
    clippingRectangle.y = point.GetY();
    clippingRectangle.w = w;
    clippingRectangle.h = h;
}

void Sprite::Render(const Point& point, float angle)
{
    SDL_Rect dstRect
    {
        .x = (int)point.GetX(),
        .y = (int)point.GetY(),
        .w = (int)(clippingRectangle.w*scaleX),
        .h = (int)(clippingRectangle.h*scaleY)
    };

    // SDL_RenderCopyEx accepts an angle in degrees. So, we convert from
    // radians, which is the standard for the whole project.
    float rotationAngle = angle*180.0/M_PI;

    SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), texture,
                     &clippingRectangle, &dstRect, rotationAngle, NULL,
                     SDL_FLIP_NONE);
}