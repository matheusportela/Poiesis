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
    int energy;
    int upperThreshold = CFG_GETI("GROWTH_UPPER_THRESHOLD");
    int lowerThreshold = CFG_GETI("GROWTH_LOWER_THRESHOLD");
    float collisionRadius;
    Random r;
    bool canConsumeEnergy = false;

    timer.Update(dt);

    if (timer.HasFired())
    {
        timer.SetTime(CFG_GETF("GROWTH_ENERGY_CONSUMING_PERIOD"));
        canConsumeEnergy = true;
    }

    for (auto entity : entities)
    {
        growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "GrowthComponent"));
        spriteComponent = std::static_pointer_cast<SpriteComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "SpriteComponent"));
        colliderComponent = std::static_pointer_cast<ColliderComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "ColliderComponent"));

        energy = growthComponent->GetEnergy();
        level = growthComponent->GetLevel();

        if (canConsumeEnergy)
        {
            if (r.GenerateFloat() < CFG_GETF("GROWTH_ENERGY_CONSUMING_CHANCE"))
                energy -= 1;
        }

        if (energy >= upperThreshold)
        {
            energy = 0;
            level += 1;
            LOG_I("[GrowthSystem] Entity \"" << entity->GetId() << "\" has "
                << "grown to level " << level);
        }
        else if (energy <= lowerThreshold)
        {
            energy = 0;
            level -= 1;
            LOG_I("[GrowthSystem] Entity \"" << entity->GetId() << "\" has "
                << "shrunk to level " << level);
        }

        if (level > max_level)
            level = max_level;
        else if (level <= 0)
        {
            Engine::GetInstance().GetEntityManager()->DeleteEntity(entity);
            continue;
        }

        collisionRadius = level*colliderComponent->GetInitRadius();

        growthComponent->SetEnergy(energy);
        growthComponent->SetLevel(level);
        spriteComponent->SetScale(level);
        colliderComponent->SetRadius(collisionRadius);
    }
}