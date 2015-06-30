// First level consists of a cell that must grow in order to survive.

#ifndef LEVEL_1_H_
#define LEVEL_1_H_

#include <memory>

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"
#include "poiesis/systems/AISystem.h"
#include "poiesis/systems/CameraSystem.h"
#include "poiesis/systems/CellSpawningSystem.h"
#include "poiesis/systems/CollisionSystem.h"
#include "poiesis/systems/CombatPowerSystem.h"
#include "poiesis/systems/DebugSystem.h"
#include "poiesis/systems/FoodSpawningSystem.h"
#include "poiesis/systems/GrowthSystem.h"
#include "poiesis/systems/InputSystem.h"
#include "poiesis/systems/ParticleSystem.h"
#include "poiesis/systems/RenderingSystem.h"

class Level1 : public Level
{
  public:
    void Start();
    void Update();
    void Finish();
    void ExitButtonCallback();

  private:
    bool win;
};

#endif // LEVEL_1_H_