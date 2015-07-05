#include "poiesis/systems/CombatPowerSystem.h"

std::string CombatPowerSystem::GetName()
{
    return "CombatPowerSystem";
}

void CombatPowerSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[CombatPowerSystem] Update: " << dt);

    auto combatEntities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("CombatComponent");

    for (auto entity : combatEntities)
    {
        if (Engine::GetInstance().HasComponent(entity, "GrowthComponent"))
        {
            auto combatComponent = std::static_pointer_cast<CombatComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "CombatComponent"));
            auto growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "GrowthComponent"));

            int power = growthComponent->GetLevel();
            combatComponent->SetPower(power);
        }
    }
}