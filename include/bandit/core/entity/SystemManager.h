// Manages systems update.

#ifndef SYSTEM_MANAGER_H_
#define SYSTEM_MANAGER_H_

#include <memory>

#include "bandit/core/Log.h"
#include "bandit/core/entity/System.h"

class SystemManager
{
  public:
    void AddSystem(std::shared_ptr<System> system);
    void Update(float dt);

  private:
    std::vector<std::shared_ptr<System>> systems;
};

#endif // SYSTEM_MANAGER_H_