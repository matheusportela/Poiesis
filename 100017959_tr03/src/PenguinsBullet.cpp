// @file   PenguinsBullet.h
// @author Matheus Vieira Portela
// @date   07/05/2015
//
// @brief Penguins's bullet game object

#include "PenguinsBullet.h"

PenguinsBullet::PenguinsBullet(const Point& position, float angle)
{
    SetRotation(angle);
    SetSprite(CFG_GETP("PENGUINS_BULLET_SPRITE"));
    SetCenter(position);
    distanceLeft = CFG_GETF("PENGUINS_BULLET_MAX_DISTANCE");

    Vector newSpeed;
    newSpeed.SetPolar(CFG_GETI("PENGUINS_BULLET_SPEED"), angle);
    SetSpeed(newSpeed);
}

void PenguinsBullet::NotifyCollision(std::shared_ptr<GameObject> other)
{
    if (other->Is("Alien"))
        distanceLeft = 0;
}

bool PenguinsBullet::Is(std::string type)
{
    return (type == "PenguinsBullet" || Bullet::Is(type));
}