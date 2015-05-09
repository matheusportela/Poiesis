// @file   PenguinsBullet.h
// @author Matheus Vieira Portela
// @date   07/05/2015
//
// @brief Penguins's bullet game object

#include "PenguinsBullet.h"

PenguinsBullet::PenguinsBullet(const Point& position, float angle) :
    Bullet(position, angle,
        CFG_GETI("PENGUINS_BULLET_SPEED"),
        CFG_GETF("PENGUINS_BULLET_MAX_DISTANCE"),
        CFG_GETP("PENGUINS_BULLET_SPRITE"),
        CFG_GETI("PENGUINS_BULLET_NUM_FRAMES"),
        CFG_GETF("PENGUINS_BULLET_FRAME_DURATION"))
{
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