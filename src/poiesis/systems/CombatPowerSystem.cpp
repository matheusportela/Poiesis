#include "poiesis/systems/CombatPowerSystem.h"

std::string CombatPowerSystem::GetName()
{
    return "CombatPowerSystem";
}

void CombatPowerSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[CombatPowerSystem] Update: " << dt);

    auto combatEntities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("CombatComponent");

    for (auto entity : combatEntities)
    {
        auto combatComponent = std::static_pointer_cast<CombatComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "CombatComponent"));
        auto growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "GrowthComponent"));

        int power = growthComponent->GetLevel();
        combatComponent->SetPower(power);
    }
}