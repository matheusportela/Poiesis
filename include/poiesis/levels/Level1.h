// First level consists of a penguin that moves around the world.

#ifndef LEVEL_1_H_
#define LEVEL_1_H_

#include <memory>

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"
#include "poiesis/systems/CameraSystem.h"
#include "poiesis/systems/CollisionSystem.h"
#include "poiesis/systems/FoodSpawningSystem.h"
#include "poiesis/systems/GrowthSystem.h"
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