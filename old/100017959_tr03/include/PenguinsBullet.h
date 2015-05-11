// @file   PenguinsBullet.h
// @author Matheus Vieira Portela
// @date   07/05/2015
//
// @brief Penguins's bullet game object

#ifndef PENGUINS_BULLET_H_
#define PENGUINS_BULLET_H_

#include "Bullet.h"

class PenguinsBullet : public Bullet
{
  public:
    PenguinsBullet(const Point& position, float angle);

    // Executes behavior during collision.
    void NotifyCollision(std::shared_ptr<GameObject> other);

    // True if type is "PenguinsBullet".
    bool Is(std::string type);
};

#endif // PENGUINS_BULLET_H_