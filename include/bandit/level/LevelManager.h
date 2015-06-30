// Manages level start, execution, finish and changing.

#ifndef LEVEL_MANAGER_H_
#define LEVEL_MANAGER_H_

#include <memory>

#include "bandit/core/Log.h"
#include "bandit/level/Level.h"

class LevelManager
{
  public:
    void SetCurrentLevel(std::shared_ptr<Level> currentLevel);
    void SetNextLevel(std::shared_ptr<Level> nextLevel);
    void Update();
    bool HasFinished();

  private:
    std::shared_ptr<Level> currentLevel;
    std::shared_ptr<Level> nextLevel;
    bool newLevel;
};

#endif // LEVEL_MANAGER_H_