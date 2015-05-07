// @file   Bullet.h
// @author Matheus Vieira Portela
// @date   20/04/2015
//
// @brief Minion's bullet game object

#include "MinionBullet.h"

MinionBullet::MinionBullet(const Point& position, float angle)
{
    SetRotation(angle);
    SetSprite(CFG_GETP("MINION_BULLET_SPRITE"));
    SetCenter(position);
    distanceLeft = CFG_GETF("MINION_BULLET_MAX_DISTANCE");

    Vector newSpeed;
    newSpeed.SetPolar(CFG_GETI("MINION_BULLET_SPEED"), angle);
    SetSpeed(newSpeed);
}

void MinionBullet::NotifyCollision(std::shared_ptr<GameObject> other)
{
    if (other->Is("Penguins"))
        distanceLeft = 0;
}

bool MinionBullet::Is(std::string type)
{
    return (type == "Bullet" || Bullet::Is(type));
}