// @file   GameObject.cpp
// @author Matheus Vieira Portela
// @date   04/05/2015
//
// @brief Abstract class for every object in the game

#include "GameObject.h"
#include "Camera.h"

Rect GameObject::GetBox() const
{
    return box;
}

Point GameObject::GetPoint() const
{
    return box.GetPoint();
}

Point GameObject::GetCenter() const
{
    return box.GetCenter();
}

float GameObject::GetRotation() const
{
    return rotation;
}

Vector GameObject::GetSpeed() const
{
    return speed;
}

void GameObject::SetSpeed(const Vector& speed)
{
    this->speed = speed;
}

void GameObject::SetSprite(std::string file)
{
    sprite = std::unique_ptr<Sprite>(new Sprite(file));
}

void GameObject::SetCenter(const Point& center)
{
    if (sprite)
    {
        box.SetCenter(center, sprite->GetWidth(), sprite->GetHeight());
    }
    else
    {
        LOG_W("[GameObject] Setting center without sprite");
        box.SetCenter(center, 0, 0);
    }
}

void GameObject::SetRotation(float rotation)
{
    this->rotation = rotation;
}

void GameObject::RenderSprite()
{
    if (sprite)
    {
        Point renderPoint = Camera::WorldToScreenPoint(GetPoint());
        sprite->Render(renderPoint, rotation);
    }
}