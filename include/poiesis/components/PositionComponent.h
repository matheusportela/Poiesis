// Stores an entity position in the world.

#ifndef POSITION_COMPONENT_H_
#define POSITION_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class PositionComponent : public Component
{
  public:
    PositionComponent(float x, float y, bool movable = false);
    std::string GetComponentClass();
    float x;
    float y;
    bool movable;
};

#endif // POSITION_COMPONENT_H_