// Stores an entity position in the world.

#ifndef POSITION_COMPONENT_H_
#define POSITION_COMPONENT_H_

#include <string>

#include "bandit/core/entity/Component.h"

class PositionComponent : public Component
{
  public:
    std::string GetComponentClass();
    float x;
    float y;
};

#endif // POSITION_COMPONENT_H_