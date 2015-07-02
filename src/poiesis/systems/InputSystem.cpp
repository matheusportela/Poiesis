#include "poiesis/systems/InputSystem.h"

std::string InputSystem::GetName()
{
    return "InputSystem";
}

void InputSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[RenderingSystem] Update: " << dt);

    ProcessButtonClick();
    ProcessPlayerImpulse();
    // ProcessParticleForceInput();
}

void InputSystem::ProcessButtonClick()
{
    if (!Engine::GetInstance().CheckInputOccurred(InputType::MousePress))
        return;

    Vector mousePosition = Engine::GetInstance().GetMousePosition();
    Rectangle rectangle;
    std::shared_ptr<ButtonComponent> buttonComponent;
    auto entities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("ButtonComponent");

    for (auto entity : entities)
    {
        if (!Engine::GetInstance().HasComponent(entity, "ButtonComponent"))
            continue;

        buttonComponent = std::static_pointer_cast<ButtonComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "ButtonComponent"));
        rectangle = buttonComponent->GetRectangle();

        if (rectangle.IsInside(mousePosition))
        {
            auto callback = buttonComponent->GetCallback();
            callback();
        }
    }
}

void InputSystem::ProcessPlayerImpulse()
{
    if (!Engine::GetInstance().HasEntityWithComponentOfClass("PlayerComponent"))
        return;

    auto playerEntity = Engine::GetInstance().GetEntityWithComponentOfClass("PlayerComponent");
    auto colliderComponent = std::static_pointer_cast<ColliderComponent>(Engine::GetInstance().GetSingleComponentOfClass(playerEntity, "ColliderComponent"));
    auto particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetSingleComponentOfClass(playerEntity, "ParticleComponent"));
    auto mousePosition = Engine::GetInstance().GetMousePosition();

    Vector cameraOffset;

    if (Engine::GetInstance().HasEntityWithComponentOfClass("CameraComponent"))
    {
        auto cameraEntity = Engine::GetInstance().GetEntityWithComponentOfClass("CameraComponent");
        auto cameraComponent = std::static_pointer_cast<CameraComponent>(Engine::GetInstance().GetSingleComponentOfClass(cameraEntity, "CameraComponent"));
        Vector screenOffset = Vector(CFG_GETI("WINDOW_WIDTH"), CFG_GETI("WINDOW_HEIGHT"))*0.5;
        cameraOffset = cameraComponent->GetPosition() - screenOffset;
    }

    Vector worldClickPosition = mousePosition + cameraOffset;

    if (Engine::GetInstance().CheckInputOccurred(InputType::MousePress) and
        worldClickPosition.CalculateDistance(particleComponent->GetPosition()) < colliderComponent->GetRadius())
    {
        LOG_W("[InputSystem] Impulse begin");
        impulseBegin = mousePosition;
        processingImpulse = true;
    }
    else if (processingImpulse and
        Engine::GetInstance().CheckInputOccurred(InputType::MouseRelease))
    {
        LOG_W("[InputSystem] Impulse end");
        impulseEnd = mousePosition;

        // particleComponent->SetPosition(mousePosition + cameraOffset);
        Vector force = particleComponent->GetForce();
        force += (impulseEnd - impulseBegin)*100.0;
        particleComponent->SetForce(force);
        processingImpulse = false;
    }
    else
    {
        return;
    }
}

void InputSystem::ProcessParticleForceInput()
{
    if (!Engine::GetInstance().CheckInputOccurred(InputType::MousePress))
        return;

    Vector mousePosition = Engine::GetInstance().GetMousePosition();
    auto entities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("MoveableComponent");
    auto cameraEntities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("CameraComponent");
    std::shared_ptr<MoveableComponent> moveableComponent;
    std::shared_ptr<ParticleComponent> particleComponent;
    Vector cameraOffset;
    Vector particlePosition;
    Vector inputForce;
    Vector resultantForce;
    float distance;

    if (cameraEntities.size() > 0)
    {
        auto cameraComponent = std::static_pointer_cast<CameraComponent>(Engine::GetInstance().GetSingleComponentOfClass(cameraEntities[0], "CameraComponent"));
        Vector screenOffset = Vector(CFG_GETI("WINDOW_WIDTH"), CFG_GETI("WINDOW_HEIGHT"))*0.5;
        cameraOffset = cameraComponent->GetPosition() - screenOffset;
    }

    mousePosition += cameraOffset;

    for (auto entity : entities)
    {
        moveableComponent = std::static_pointer_cast<MoveableComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "MoveableComponent"));
        particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "ParticleComponent"));

        if (moveableComponent->GetActive())
        {
            particlePosition = particleComponent->GetPosition();
            distance = particlePosition.CalculateDistance(mousePosition);
            inputForce = mousePosition - particlePosition;
            inputForce.Normalize();
            inputForce *= -CFG_GETF("INPUT_FORCE")/(1 + distance); // Summing with 1 to avoid division by zero.
            resultantForce = inputForce + particleComponent->GetForce();
            particleComponent->SetForce(resultantForce);

            LOG_D("[InputSystem] Particle position: " << particlePosition);
            LOG_D("[InputSystem] Mouse position: " << mousePosition);
            LOG_D("[InputSystem] Distance: " << distance);
            LOG_D("[InputSystem] Force: " << inputForce);
            LOG_D("[InputSystem] Resultant force: " << resultantForce);
        }
    }
}