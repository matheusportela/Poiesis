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
    Random random;
    float growthChance = CFG_GETF("GROWTH_CHANCE");
    int level;
    int power;
    int threshold;

    for (auto entity : entities)
    {
        growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "GrowthComponent"));
        spriteComponent = std::static_pointer_cast<SpriteComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "SpriteComponent"));

        power = growthComponent->GetPower();
        level = growthComponent->GetLevel();
        threshold = growthComponent->GetThreshold();

        if (random.GenerateFloat() < growthChance)
            power += 1;

        if (power > threshold)
        {
            power = 0;
            level += 1;
            LOG_I("[GrowthSystem] Entity \"" << entity->GetId() << "\" has "
                << "grown to level " << level);
        }

        growthComponent->SetPower(power);
        growthComponent->SetLevel(level);
        spriteComponent->SetScale(level);
    }
}