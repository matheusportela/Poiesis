// @file   Bullet.h
// @author Matheus Vieira Portela
// @date   20/04/2015
//
// @brief Minion's bullet game object

#ifndef BULLET_H_
#define BULLET_H_

#include <memory>
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
    Bullet(const Point& position, float angle);
    ~Bullet();

    // Updates bullet position.
    void UpdatePosition(const Vector& displacement);

    // Updates distance left before destruction.
    void UpdateDistanceLeft(const Vector& displacement);

    // Defining GameObject virtual methods.
    void Update(float dt);
    void Render();
    bool IsDead();

  private:
    // Bullet's sprite.
    std::unique_ptr<Sprite> sprite;

    // Bullet's speed.
    Vector speed;

    // Amount of distance the bullet still have before being destroyed.
    float distanceLeft;
};

#endif // BULLET_H_