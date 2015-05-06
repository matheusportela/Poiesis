// @file   Bullet.cpp
// @author Matheus Vieira Portela
// @date   20/04/2015
//
// @brief Minion's bullet game object

#include "Bullet.h"

Bullet::Bullet(const Point& position, float angle)
{
    SetRotation(angle);
    SetSprite(CFG_GETP("BULLET_SPRITE"));
    SetCenter(position);
    distanceLeft = CFG_GETF("BULLET_MAX_DISTANCE");

    Vector newSpeed;
    newSpeed.SetPolar(CFG_GETI("BULLET_SPEED"), angle);
    SetSpeed(newSpeed);
}

Bullet::~Bullet()
{
}

void Bullet::UpdatePosition(const Vector& displacement)
{
    Point bulletCenter = GetCenter();
    bulletCenter.Add(displacement);
    SetCenter(bulletCenter);
}

void Bullet::UpdateDistanceLeft(const Vector& displacement)
{
    distanceLeft -= displacement.GetMagnitude();
}

void Bullet::Update(float dt)
{
    Vector displacement = GetSpeed();
    displacement.Multiply(dt);

    UpdatePosition(displacement);
    UpdateDistanceLeft(displacement);
}

void Bullet::Render()
{
    RenderSprite();
}

bool Bullet::IsDead()
{
    return (distanceLeft <= 0);
}

void Bullet::NotifyCollision(std::shared_ptr<GameObject> other)
{
    if (other->Is("Alien"))
        distanceLeft = 0;
}

bool Bullet::Is(std::string type)
{
    return (type == "Bullet");
}