// @file   MinionBullet.h
// @author Matheus Vieira Portela
// @date   07/05/2015
//
// @brief Minion's bullet game object

#ifndef MINION_BULLET_H_
#define MINION_BULLET_H_

#include "Bullet.h"

class MinionBullet : public Bullet
{
  public:
    MinionBullet(const Point& position, float angle);

    // Executes behavior during collision.
    void NotifyCollision(std::shared_ptr<GameObject> other);

    // True if type is "MinionBullet".
    bool Is(std::string type);
};

#endif // MINION_BULLET_H_