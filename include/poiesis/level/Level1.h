// First level consists of a penguin that moves around the world.

#ifndef LEVEL_1_H_
#define LEVEL_1_H_

#include <memory>

#include "bandit/core/Log.h"
#include "bandit/core/entity/Entity.h"
#include "bandit/core/entity/EntityManager.h"
#include "bandit/core/entity/SystemManager.h"
#include "bandit/core/level/Level.h"

#include "bandit/component/SpriteComponent.h"

class Level1 : public Level
{
  public:
    Level1(std::shared_ptr<EntityManager> entityManager,
        std::shared_ptr<SystemManager> systemManager);
    void Start();
    void Update();
    void Finish();

  private:
    std::shared_ptr<EntityManager> entityManager;
    std::shared_ptr<SystemManager> systemManager;
};

#endif // LEVEL_1_H_