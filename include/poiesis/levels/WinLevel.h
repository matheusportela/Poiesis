// Win level consists of a message telling the user won the game.

#ifndef WIN_LEVEL_H_
#define WIN_LEVEL_H_

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"
#include "poiesis/levels/EntryLevel.h"
#include "poiesis/systems/DebugSystem.h"
#include "poiesis/systems/InputSystem.h"
#include "poiesis/systems/RenderingSystem.h"

class WinLevel : public Level
{
  public:
    void Start();
    void Update();
    void Finish();
    void MenuButtonCallback();
};

#endif // WIN_LEVEL_H_