#include "poiesis/systems/PlayerMovementSystem.h"

std::string PlayerMovementSystem::GetName()
{
    return "PlayerMovementSystem";
}

void PlayerMovementSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[PlayerMovementSystem] Update: " << dt);
    
    if (!Engine::GetInstance().GetInputAdapter()->CheckInputOccurred(InputType::MouseDown))
        return;

    auto entities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("PositionComponent");
    std::shared_ptr<PositionComponent> positionComponent;

    for (auto entity : entities)
    {
        positionComponent = std::static_pointer_cast<PositionComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "PositionComponent"));
        positionComponent->x += 10;
        LOG_D("Position: " << positionComponent->x << " " << positionComponent->y);
    }
}
