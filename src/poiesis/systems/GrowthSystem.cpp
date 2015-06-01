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
    int level;
    int power;
    int threshold;

    for (auto entity : entities)
    {
        growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "GrowthComponent"));
        spriteComponent = std::static_pointer_cast<SpriteComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "SpriteComponent"));

        power = growthComponent->GetPower();
        level = growthComponent->GetLevel();
        threshold = 0;

        if (power > threshold)
        {
            power = 0;
            level += 1;
            LOG_I("[GrowthSystem] Entity \"" << entity->GetId() << "\" has "
                << "grown to level " << level);
        }

        // if (level > 3)
        //     level = 3;

        growthComponent->SetPower(power);
        growthComponent->SetLevel(level);
        spriteComponent->SetScale(level);
    }
}