// @file   Bullet.cpp
// @author Matheus Vieira Portela
// @date   20/04/2015
//
// @brief Minion's bullet game object

#include "Bullet.h"

Bullet::Bullet(const Point& position, float angle, float speed,
    float maxDistance, std::string sprite, int numFrames, float frameDuration) :
    AnimatedGameObject(sprite, numFrames, frameDuration, false)
{
    SetRotation(angle);
    SetCenter(position);
    InitializeSpeed(speed, angle);
    distanceLeft = maxDistance;
}

void Bullet::InitializeSpeed(float magnitude, float angle)
{
    Vector newSpeed;
    newSpeed.SetPolar(magnitude, angle);
    SetSpeed(newSpeed);
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
    Vector displacement = GetSpeed()*dt;

    UpdatePosition(displacement);
    UpdateDistanceLeft(displacement);
    AnimatedGameObject::Update(dt);
}

void Bullet::Render()
{
    AnimatedGameObject::Render();
}

bool Bullet::IsDead()
{
    return (distanceLeft <= 0);
}

void Bullet::NotifyCollision(std::shared_ptr<GameObject> other)
{
}

bool Bullet::Is(std::string type)
{
    return (type == "Bullet");
}