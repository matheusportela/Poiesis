// Process entities with renderable components and render sprites.

#ifndef RENDERING_SYSTEM_H_
#define RENDERING_SYSTEM_H_

#include <memory>
#include <string>

#include "bandit/adapters/GraphicsAdapter.h"
#include "bandit/core/Log.h"
#include "bandit/core/entity/EntityManager.h"
#include "bandit/core/entity/System.h"
#include "bandit/component/SpriteComponent.h"

class RenderingSystem : public System
{
  public:
    RenderingSystem(std::shared_ptr<EntityManager> entityManager,
        std::shared_ptr<GraphicsAdapter> graphicsAdapter);
    std::string GetName();
    void Update(float dt);

  private:
    std::shared_ptr<GraphicsAdapter> graphicsAdapter;
};

#endif // RENDERING_SYSTEM_H_