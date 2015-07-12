// Second level consists of a cell that must complexify in order to survive.

#ifndef LEVEL_2_H_
#define LEVEL_2_H_

#include <memory>

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"

#include "poiesis/components/AIComponent.h"

#include "poiesis/levels/EntryLevel.h"
#include "poiesis/levels/Level3.h"
#include "poiesis/levels/LoseLevel.h"

#include "poiesis/systems/AISystem.h"
#include "poiesis/systems/AnimationSystem.h"
#include "poiesis/systems/CameraSystem.h"
#include "poiesis/systems/CollisionSystem.h"
#include "poiesis/systems/CombatPowerSystem.h"
#include "poiesis/systems/ComplexitySystem.h"
#include "poiesis/systems/DebugSystem.h"
#include "poiesis/systems/InputSystem.h"
#include "poiesis/systems/ParticleSystem.h"
#include "poiesis/systems/RenderingSystem.h"
#include "poiesis/systems/SpawningSystem.h"

class Level2 : public Level
{
  public:
    void Start();
    void CreateAllEntities();
    void CreateButtons();
    void CreateCells();
    void CreateFood();
    void CreateCellParticles();
    void CreateAllSystems();
    void CreateEssentialSystems();
    void CreateAccessorySystems();
    void DeleteAccessorySystems();
    void Update();
    void Finish();
    void ZoomOutEffect();
    void MenuButtonCallback();
    void PauseButtonCallback();
    void ExitButtonCallback();

  private:
    bool finished;
    bool paused;

    std::shared_ptr<Entity> pauseMenuExitButton;
};

#endif // LEVEL_2_H_