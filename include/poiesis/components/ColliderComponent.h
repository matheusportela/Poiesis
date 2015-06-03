// Stores data relevant for collision between entities.

#ifndef COLLIDER_COMPONENT_H_
#define COLLIDER_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class ColliderComponent : public Component
{
  public:
    ColliderComponent(float radius);
    std::string GetComponentClass();

    float GetRadius();
    void SetRadius(float radius);
    float GetInitRadius();

  private:
    // Holds the radius that must be considered for collisions.
    float radius;

    // Holds the radius given at construction time. This is important for
    // systems that change collision radius and wish to keep track of the first
    // given radius.
    float initRadius;
};

#endif // COLLIDER_COMPONENT_H_