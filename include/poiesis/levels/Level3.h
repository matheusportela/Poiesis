// Third level consists of a cell that must reproduce in order to survive.

#ifndef LEVEL_3_H_
#define LEVEL_3_H_

#include <memory>

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"

#include "poiesis/components/InfectionComponent.h"
#include "poiesis/components/ReproductionComponent.h"

#include "poiesis/levels/EntryLevel.h"
#include "poiesis/levels/LoseLevel.h"
#include "poiesis/levels/WinLevel.h"

#include "poiesis/systems/AISystem.h"
#include "poiesis/systems/AnimationSystem.h"
#include "poiesis/systems/CameraSystem.h"
#include "poiesis/systems/CollisionSystem.h"
#include "poiesis/systems/CombatPowerSystem.h"
#include "poiesis/systems/DebugSystem.h"
#include "poiesis/systems/InfectionSystem.h"
#include "poiesis/systems/InputSystem.h"
#include "poiesis/systems/ParticleSystem.h"
#include "poiesis/systems/RenderingSystem.h"
#include "poiesis/systems/ReproductionSystem.h"
#include "poiesis/systems/SpawningSystem.h"

class Level3 : public Level
{
  public:
    void Start();
    void CreateAllEntities();
    void CreateButtons();
    void CreateAreas();
    void CreateCells();
    void CreateBacteria();
    void CreateViruses();
    void CreateFood();
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
    std::shared_ptr<Entity> pauseMenuButton;
};

#endif // LEVEL_3_H_