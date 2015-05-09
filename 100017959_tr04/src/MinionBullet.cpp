// @file   MinionBullet.h
// @author Matheus Vieira Portela
// @date   07/05/2015
//
// @brief Minion's bullet game object

#include "MinionBullet.h"

MinionBullet::MinionBullet(const Point& position, float angle) :
    Bullet(position, angle,
        CFG_GETI("MINION_BULLET_SPEED"),
        CFG_GETF("MINION_BULLET_MAX_DISTANCE"),
        CFG_GETP("MINION_BULLET_SPRITE"),
        CFG_GETI("MINION_BULLET_NUM_FRAMES"),
        CFG_GETF("MINION_BULLET_FRAME_DURATION"))
{
}

void MinionBullet::NotifyCollision(std::shared_ptr<GameObject> other)
{
    if (other->Is("Penguins"))
        distanceLeft = 0;
}

bool MinionBullet::Is(std::string type)
{
    return (type == "MinionBullet" || Bullet::Is(type));
}