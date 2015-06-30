// Entry level consists of an entry menu before starting the game.

#ifndef ENTRY_LEVEL_H_
#define ENTRY_LEVEL_H_

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"
#include "poiesis/levels/Level1.h"
#include "poiesis/systems/DebugSystem.h"
#include "poiesis/systems/InputSystem.h"

class EntryLevel : public Level
{
  public:
    void Start();
    void Update();
    void Finish();
    void StartButtonCallback();
};

#endif // ENTRY_LEVEL_H_