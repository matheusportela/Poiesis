// Stores data relevant for collision between entities.

#ifndef PLAYER_COMPONENT_H_
#define PLAYER_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class PlayerComponent : public Component
{
  public:
    std::string GetComponentClass();
};

#endif // PLAYER_COMPONENT_H_