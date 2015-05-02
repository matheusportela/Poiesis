// @file   Bullet.h
// @author Matheus Vieira Portela
// @date   20/04/2015
//
// @brief Minion's bullet game object

#ifndef BULLET_H_
#define BULLET_H_

#include <queue>

#include "Camera.h"
#include "ConfigParser.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Point.h"
#include "Vector.h"

class Bullet : public GameObject
{
  public:
    Bullet(Point point, float angle);
    ~Bullet();

    // Updates bullet position.
    void UpdatePosition(Vector displacement);

    // Updates distance left before destruction.
    void UpdateDistanceLeft(Vector displacement);

    // Defining GameObject virtual methods.
    void Update(float dt);
    void Render();
    bool IsDead();

  private:
    // Bullet's sprite.
    Sprite* sprite;

    // Bullet's speed.
    Vector speed;

    // Amount of distance the bullet still have before being destroyed.
    float distanceLeft;
};

#endif // BULLET_H_