#include "poiesis/systems/PlayerMovementSystem.h"

std::string PlayerMovementSystem::GetName()
{
    return "PlayerMovementSystem";
}

void PlayerMovementSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[RenderingSystem] Update: " << dt);
    
    if (!Engine::GetInstance().GetInputAdapter()->CheckInputOccurred(InputType::MousePress))
        return;

    int mouseX = Engine::GetInstance().GetInputAdapter()->GetMouseX();
    int mouseY = Engine::GetInstance().GetInputAdapter()->GetMouseY();
    std::vector<std::shared_ptr<Entity>> entities =
        Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("MovementComponent");
    std::vector<std::shared_ptr<Component>> components;

    for (std::shared_ptr<Entity> entity : entities)
    {
        components = entityManager->GetComponentsOfClass(entity, "PositionComponent");
        for (std::shared_ptr<Component> component : components)
        {
            std::shared_ptr<PositionComponent> positionComponent =
                std::static_pointer_cast<PositionComponent>(component);

            LOG_D("Position: " << positionComponent->x << " " << positionComponent->y);
        }
    }
}
