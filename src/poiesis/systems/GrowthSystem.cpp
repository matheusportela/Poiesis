#include "poiesis/systems/GrowthSystem.h"

std::string GrowthSystem::GetName()
{
    return "GrowthSystem";
}

void GrowthSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[GrowthSystem] Update: " << dt);

    auto entities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("GrowthComponent");
    std::shared_ptr<GrowthComponent> growthComponent;
    std::shared_ptr<SpriteComponent> spriteComponent;
    std::shared_ptr<ColliderComponent> colliderComponent;
    int max_level = CFG_GETI("GROWTH_LEVEL_LIMIT");
    int level;
    int power;
    int threshold;
    float collisionRadius;

    for (auto entity : entities)
    {
        growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "GrowthComponent"));
        spriteComponent = std::static_pointer_cast<SpriteComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "SpriteComponent"));
        colliderComponent = std::static_pointer_cast<ColliderComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "ColliderComponent"));

        power = growthComponent->GetPower();
        level = growthComponent->GetLevel();
        collisionRadius = colliderComponent->GetRadius();
        threshold = 0;

        if (power > threshold)
        {
            power = 0;
            level += 1;
            collisionRadius = level*colliderComponent->GetInitRadius();
            LOG_I("[GrowthSystem] Entity \"" << entity->GetId() << "\" has "
                << "grown to level " << level);
        }

        if (level > max_level)
        {
            level = max_level;
            collisionRadius = level*colliderComponent->GetInitRadius();
        }

        growthComponent->SetPower(power);
        growthComponent->SetLevel(level);
        spriteComponent->SetScale(level);
        colliderComponent->SetRadius(collisionRadius);
    }
}