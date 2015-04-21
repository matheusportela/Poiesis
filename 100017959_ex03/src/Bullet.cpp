// @file   Bullet.cpp
// @author Matheus Vieira Portela
// @date   20/04/2015
//
// @brief Minion's bullet game object

#include "Bullet.h"

Bullet::Bullet(Point point, float angle)
{
    rotation = angle;
    sprite = new Sprite(CFG_GETP("BULLET_SPRITE"));
    box.SetCenter(point, sprite->GetWidth(), sprite->GetHeight());
    distanceLeft = CFG_GETF("BULLET_MAX_DISTANCE");
    speed.SetPolar(CFG_GETF("BULLET_SPEED"), angle);
}

Bullet::~Bullet()
{
    delete sprite;
}

void Bullet::UpdatePosition(Vector displacement)
{
    Point bulletCenter;

    bulletCenter = GetCenter();
    bulletCenter.Add(displacement);
    box.SetCenter(bulletCenter, sprite->GetWidth(), sprite->GetHeight());
}

void Bullet::UpdateDistanceLeft(Vector displacement)
{
    distanceLeft -= displacement.GetMagnitude();
}

void Bullet::Update(float dt)
{
    Vector displacement;
    displacement = speed;
    displacement.Multiply(dt);

    UpdatePosition(displacement);
    UpdateDistanceLeft(displacement);
}

void Bullet::Render()
{
    Point renderPoint;
    renderPoint = Camera::WorldToScreenPoint(box.GetPoint());
    sprite->Render(renderPoint, rotation);
}

bool Bullet::IsDead()
{
    return (distanceLeft <= 0);
}