// First level consists of a cell that must complexify in order to survive.

#ifndef LEVEL_2_H_
#define LEVEL_2_H_

#include <memory>

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"
#include "poiesis/levels/EntryLevel.h"
#include "poiesis/levels/LoseLevel.h"
#include "poiesis/levels/WinLevel.h"
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

class Level2 : public Level
{
  public:
    void Start();
    void CreateAllEntities();
    void CreateButtons();
    void CreateCells();
    void CreateAllSystems();
    void CreateEssentialSystems();
    void CreateAccessorySystems();
    void DeleteAccessorySystems();
    void Update();
    void Finish();
    void MenuButtonCallback();
    void PauseButtonCallback();
    void ExitButtonCallback();

  private:
    bool win;
    bool paused;

    std::shared_ptr<Entity> pauseMenuExitButton;
};

#endif // LEVEL_2_H_