// @file   Bullet.cpp
// @author Matheus Vieira Portela
// @date   20/04/2015
//
// @brief Minion's bullet game object

#include "Bullet.h"

Bullet::Bullet(const Point& position, float angle)
{
    rotation = angle;
    sprite = std::unique_ptr<Sprite>(new Sprite(CFG_GETP("BULLET_SPRITE")));
    box.SetCenter(position, sprite->GetWidth(), sprite->GetHeight());
    distanceLeft = CFG_GETF("BULLET_MAX_DISTANCE");
    speed.SetPolar(CFG_GETI("BULLET_SPEED"), angle);
}

Bullet::~Bullet()
{
}

void Bullet::UpdatePosition(const Vector& displacement)
{
    Point bulletCenter = GetCenter();
    bulletCenter.Add(displacement);
    box.SetCenter(bulletCenter, sprite->GetWidth(), sprite->GetHeight());
}

void Bullet::UpdateDistanceLeft(const Vector& displacement)
{
    distanceLeft -= displacement.GetMagnitude();
}

void Bullet::Update(float dt)
{
    Vector displacement = speed;
    displacement.Multiply(dt);

    UpdatePosition(displacement);
    UpdateDistanceLeft(displacement);
}

void Bullet::Render()
{
    Point renderPoint = Camera::WorldToScreenPoint(box.GetPoint());
    sprite->Render(renderPoint, rotation);
}

bool Bullet::IsDead()
{
    return (distanceLeft <= 0);
}