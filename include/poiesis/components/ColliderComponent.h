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

  private:
    // Holds the radius that must be considered for collisions.
    float radius;
};

#endif // COLLIDER_COMPONENT_H_