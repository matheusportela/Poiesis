// Manages systems update.

#ifndef SYSTEM_MANAGER_H_
#define SYSTEM_MANAGER_H_

#include <memory>
#include <string>

#include "bandit/core/Log.h"
#include "bandit/entity/System.h"

class SystemManager
{
  public:
    void AddSystem(std::shared_ptr<System> system);
    void DeleteSystem(std::string name);
    void Update(float dt);
    void Clear();

  private:
    std::vector<std::shared_ptr<System>> systems;
};

#endif // SYSTEM_MANAGER_H_