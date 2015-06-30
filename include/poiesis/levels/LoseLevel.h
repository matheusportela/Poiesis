// Lose level consists of a message telling the user lost the game.

#ifndef LOSE_LEVEL_H_
#define LOSE_LEVEL_H_

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"
#include "poiesis/levels/EntryLevel.h"
#include "poiesis/systems/DebugSystem.h"
#include "poiesis/systems/InputSystem.h"
#include "poiesis/systems/RenderingSystem.h"

class LoseLevel : public Level
{
  public:
    void Start();
    void Update();
    void Finish();
    void MenuButtonCallback();
};

#endif // LOSE_LEVEL_H_