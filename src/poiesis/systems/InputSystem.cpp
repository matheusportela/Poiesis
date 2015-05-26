#include "poiesis/systems/InputSystem.h"

std::string InputSystem::GetName()
{
    return "InputSystem";
}

void InputSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[RenderingSystem] Update: " << dt);

    if (!Engine::GetInstance().GetInputAdapter()->CheckInputOccurred(InputType::MousePress))
        return;

    auto entities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("MoveableComponent");
    std::shared_ptr<MoveableComponent> moveableComponent;
    std::shared_ptr<ParticleComponent> particleComponent;
    float mouseX = Engine::GetInstance().GetInputAdapter()->GetMouseX();
    float mouseY = Engine::GetInstance().GetInputAdapter()->GetMouseY();

    for (auto entity : entities)
    {
        moveableComponent = std::static_pointer_cast<MoveableComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "MoveableComponent"));
        particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "ParticleComponent"));

        if (moveableComponent->GetActive())
            particleComponent->SetPosition(Vector(mouseX, mouseY));
    }
}
