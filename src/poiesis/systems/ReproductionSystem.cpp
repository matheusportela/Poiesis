#include "poiesis/systems/ReproductionSystem.h"

std::string ReproductionSystem::GetName()
{
    return "ReproductionSystem";
}

void ReproductionSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[ReproductionSystem] Update: " << dt);

    auto combatEntities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("ReproductionComponent");

    timer.Update(dt);

    for (auto entity : combatEntities)
    {
        auto reproductionComponent = std::static_pointer_cast<ReproductionComponent>(
            Engine::GetInstance().GetSingleComponentOfClass(entity,
                "ReproductionComponent"));
        auto growthComponent = std::static_pointer_cast<GrowthComponent>(
            Engine::GetInstance().GetSingleComponentOfClass(entity,
                "GrowthComponent"));
        auto spriteComponent = std::static_pointer_cast<SpriteComponent>(
            Engine::GetInstance().GetSingleComponentOfClass(entity,
                "SpriteComponent"));

        ConsumeEnergy(growthComponent);
        spriteComponent->SetCurrentFrame(growthComponent->GetEnergy());

        if (growthComponent->GetEnergy() == CFG_GETI("LEVEL_3_MAX_ENERGY")-1)
            reproductionComponent->SetEnabled(true);
        else
            reproductionComponent->SetEnabled(false);
    }

    if (timer.HasFired())
        timer.SetTime(CFG_GETF("REPRODUCTION_ENERGY_CONSUMING_PERIOD"));
}

void ReproductionSystem::ConsumeEnergy(std::shared_ptr<GrowthComponent> growthComponent)
{
    Random r;
    int energy = growthComponent->GetEnergy();

    if (timer.HasFired() && (r.GenerateFloat() < CFG_GETF("REPRODUCTION_ENERGY_CONSUMING_CHANCE")) && energy > 0)
        --energy;

    if (energy >= CFG_GETI("LEVEL_3_MAX_ENERGY"))
        energy = CFG_GETI("LEVEL_3_MAX_ENERGY")-1;

    growthComponent->SetEnergy(energy);
}