// Entry level consists of an entry menu before starting the game.

#ifndef ENTRY_LEVEL_H_
#define ENTRY_LEVEL_H_

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"
#include "poiesis/components/ParticleComponent.h"
#include "poiesis/components/SpriteComponent.h"
#include "poiesis/levels/Level1.h"
#include "poiesis/levels/Level2.h"
#include "poiesis/levels/Level3.h"
#include "poiesis/levels/WinLevel.h"
#include "poiesis/levels/LoseLevel.h"
#include "poiesis/systems/DebugSystem.h"
#include "poiesis/systems/InputSystem.h"
#include "poiesis/systems/RenderingSystem.h"

class EntryLevel : public Level
{
  public:
    void Start();
    void Update();
    void Finish();
    void StartButtonCallback();
    void ExitButtonCallback();
    bool PreloadImages();
    bool PreloadAnimation(std::string filename, int numFrames);
    bool PreloadImage(std::string filename);

  private:
    std::shared_ptr<Entity> loading;
    bool canCreateStartButton;
};

#endif // ENTRY_LEVEL_H_