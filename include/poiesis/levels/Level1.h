// First level consists of a penguin that moves around the world.

#ifndef LEVEL_1_H_
#define LEVEL_1_H_

#include <memory>

#include "bandit/Engine.h"

#include "poiesis/components/MoveableComponent.h"
#include "poiesis/components/SpriteComponent.h"
#include "poiesis/components/ParticleComponent.h"

#include "poiesis/systems/InputSystem.h"
#include "poiesis/systems/ParticleSystem.h"

class Level1 : public Level
{
  public:
    void Start();
    void Update();
    void Finish();
};

#endif // LEVEL_1_H_