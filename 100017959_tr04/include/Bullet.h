// @file   Bullet.h
// @author Matheus Vieira Portela
// @date   20/04/2015
//
// @brief Generic bullet game object

#ifndef BULLET_H_
#define BULLET_H_

#include <memory>

#include "ConfigParser.h"
#include "AnimatedGameObject.h"
#include "Point.h"
#include "Vector.h"

class Bullet : public AnimatedGameObject
{
  public:
    Bullet(const Point& position, float angle, float speed, float maxDistance,
        std::string sprite, int numFrames, float frameDuration);

    // Initializes bullet speed vector with magnitude and angle.
    void InitializeSpeed(float magnitude, float angle);

    // Updates bullet position.
    void UpdatePosition(const Vector& displacement);

    // Updates distance left before destruction.
    void UpdateDistanceLeft(const Vector& displacement);

    // Defining GameObject virtual methods.
    void Update(float dt);

    // Renders bullet sprite.
    void Render();

    // Checks whether bullet must be deleted.
    bool IsDead();

    // Executes behavior during collision.
    void NotifyCollision(std::shared_ptr<GameObject> other);

    // True if type is "Bullet".
    bool Is(std::string type);

  protected:
    // Amount of distance the bullet still have before being destroyed.
    float distanceLeft;
};

#endif // BULLET_H_