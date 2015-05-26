// Process user input to move the player entity.

#ifndef PLAYER_MOVEMENT_SYSTEM_H_
#define PLAYER_MOVEMENT_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/components/SpriteComponent.h"
#include "poiesis/components/PositionComponent.h"

class PlayerMovementSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
};

#endif // PLAYER_MOVEMENT_SYSTEM_H_