#include <iostream>
#include <memory.h>

#include "bandit/Engine.h"
#include "bandit/adapters/sdl/SDLGraphicsAdapter.h"
#include "bandit/adapters/sdl/SDLMusicAdapter.h"
#include "bandit/adapters/sdl/SDLSoundEffectAdapter.h"
#include "bandit/adapters/sdl/SDLSystemAdapter.h"
#include "bandit/adapters/sdl/SDLTimerAdapter.h"

// Remove after tests
#include "bandit/core/entity/Component.h"
#include "bandit/core/entity/Entity.h"
#include "bandit/core/entity/EntityManager.h"
#include "bandit/core/entity/System.h"

class HealthComponent : public Component
{
  public:
    HealthComponent(int hp) : hp(hp) {}

    std::string GetComponentClass()
    {
        return "HealthComponent";
    }

    int hp;
};

class DamageSystem : public System
{
  public:
    DamageSystem(std::shared_ptr<EntityManager> entityManager) :
        System(entityManager) {}

    void Update(float dt)
    {
        LOG_I("Updating damage system");

        std::string componentClass = "HealthComponent";
        std::vector<std::shared_ptr<Entity>> entities =
            entityManager->GetAllEntitiesWithComponentOfClass(componentClass);
        std::vector<std::shared_ptr<Component>> components;

        for (std::shared_ptr<Entity> entity : entities)
        {
            components = entityManager->GetComponentsOfClass(entity, componentClass);

            for (std::shared_ptr<Component> component : components)
            {
                LOG_I("Entity " << entity->GetId() << " has health component. Damaging it");

                std::shared_ptr<HealthComponent> healthComponent = std::static_pointer_cast<HealthComponent>(component);
                healthComponent->hp -= 2;

                LOG_I("HP: " << healthComponent->hp);

                if (healthComponent->hp <= 0)
                {
                    LOG_I("Entity " << entity->GetId() << " with hp <= 0");
                    entityManager->DeleteEntity(entity);
                }
            }
        }
    }
};

int main()
{
    // LOG_SET_DEBUG();
    // Engine engine(std::make_shared<SDLSystemAdapter>(),
    //     std::make_shared<SDLTimerAdapter>(),
    //     std::make_shared<SDLGraphicsAdapter>(),
    //     std::make_shared<SDLMusicAdapter>(),
    //     std::make_shared<SDLSoundEffectAdapter>());

    // engine.Run();

    std::shared_ptr<EntityManager> entityManager = std::make_shared<EntityManager>();
    std::shared_ptr<System> damageSystem = std::make_shared<DamageSystem>(entityManager);
    std::shared_ptr<Entity> playerEntity = entityManager->CreateEntity();
    std::shared_ptr<Entity> enemyEntity = entityManager->CreateEntity();
    entityManager->AddComponent(std::make_shared<HealthComponent>(10), playerEntity);

    auto timer = std::make_shared<SDLTimerAdapter>();

    while (true)
    {
        damageSystem->Update(timer->GetElapsedTime());
        LOG_I("Number of entities: " << entityManager->entities.size());
        timer->Sleep(1);
    }
    
    return 0;
}