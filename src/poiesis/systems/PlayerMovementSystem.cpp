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

    auto mouseX = Engine::GetInstance().GetInputAdapter()->GetMouseX();
    auto mouseY = Engine::GetInstance().GetInputAdapter()->GetMouseY();
    auto components = Engine::GetInstance().GetEntityManager()->GetAllComponentsOfClass("PositionComponent");
    std::shared_ptr<PositionComponent> positionComponent;

    for (auto component : components)
    {
        positionComponent = std::static_pointer_cast<PositionComponent>(component);

        if (positionComponent->movable)
        {
            positionComponent->x = mouseX;
            positionComponent->y = mouseY;
            LOG_D("Position: " << positionComponent->x << " " << positionComponent->y);
        }
    }
}
