// Manages level start, execution, finish and changing.

#ifndef LEVEL_MANAGER_H_
#define LEVEL_MANAGER_H_

#include <memory>

#include "bandit/core/Log.h"
#include "bandit/core/level/Level.h"

class LevelManager
{
  public:
    void SetCurrentLevel(std::shared_ptr<Level> currentLevel);
    void Update();

  private:
    std::shared_ptr<Level> currentLevel;
    bool newLevel;
};

#endif // LEVEL_MANAGER_H_