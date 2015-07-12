#include "poiesis/systems/InputSystem.h"

std::string InputSystem::GetName()
{
    return "InputSystem";
}

void InputSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[RenderingSystem] Update: " << dt);

    particleForceTimer.Update(dt);

    if (!ProcessButtonClick())
    {
        if (!ProcessPlayerImpulse())
            ProcessParticleForceInput();
    }
}

bool InputSystem::ProcessButtonClick()
{
    if (!Engine::GetInstance().CheckInputOccurred(InputType::MousePress))
        return false;

    bool processed = false;
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
            LOG_I("[InputType] Clicked on button " << entity->GetId());
            auto callback = buttonComponent->GetCallback();
            callback();
            processed = true;
        }
    }

    return processed;
}

bool InputSystem::ProcessPlayerImpulse()
{
    if (!Engine::GetInstance().HasEntityWithComponentOfClass("PlayerComponent"))
        return false;

    auto playerEntity = Engine::GetInstance().GetEntityWithComponentOfClass("PlayerComponent");
    auto colliderComponent = std::static_pointer_cast<ColliderComponent>(Engine::GetInstance().GetSingleComponentOfClass(playerEntity, "ColliderComponent"));
    auto particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetSingleComponentOfClass(playerEntity, "ParticleComponent"));
    auto infectionComponent = std::static_pointer_cast<InfectionComponent>(Engine::GetInstance().GetSingleComponentOfClass(playerEntity, "InfectionComponent"));
    auto mousePosition = Engine::GetInstance().GetMousePosition();

    if (infectionComponent->GetInfectionType() == CannotInput)
    {
        processingImpulse = false;
        return true;
    }
    else if (Engine::GetInstance().CheckInputOccurred(InputType::MousePress) and
        HasClickedOnPlayer(mousePosition))
    {
        LOG_I("[InputSystem] Impulse begin");
        impulseBegin = mousePosition;
        processingImpulse = true;
        return true;
    }
    else if (processingImpulse and
        Engine::GetInstance().CheckInputOccurred(InputType::MouseRelease))
    {
        LOG_I("[InputSystem] Impulse end");
        impulseEnd = mousePosition;

        Vector resultantForce = particleComponent->GetForce();
        resultantForce += (impulseEnd - impulseBegin)*100.0;
        particleComponent->SetForce(resultantForce);
        processingImpulse = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool InputSystem::HasClickedOnPlayer(Vector mousePosition)
{
    auto playerEntity = Engine::GetInstance().GetEntityWithComponentOfClass("PlayerComponent");
    auto colliderComponent = std::static_pointer_cast<ColliderComponent>(Engine::GetInstance().GetSingleComponentOfClass(playerEntity, "ColliderComponent"));
    auto particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetSingleComponentOfClass(playerEntity, "ParticleComponent"));
    auto playerPosition = particleComponent->GetPosition();
    Vector worldClickPosition = ConvertWindowToWorldPosition(mousePosition);
    return worldClickPosition.CalculateDistance(playerPosition) <= colliderComponent->GetRadius();
}

Vector InputSystem::ConvertWindowToWorldPosition(Vector windowPosition)
{
    Vector screenOffset = Vector(CFG_GETI("WINDOW_WIDTH"), CFG_GETI("WINDOW_HEIGHT"))*0.5;
    Vector cameraPosition = GetCameraPosition();
    float cameraHeight = GetCameraHeight();
    Vector worldPosition = cameraPosition + (windowPosition - screenOffset)*cameraHeight;
    return worldPosition;
}

Vector InputSystem::GetCameraPosition()
{
    Vector cameraPosition;

    if (Engine::GetInstance().HasEntityWithComponentOfClass("CameraComponent"))
    {
        auto cameraEntity = Engine::GetInstance().GetEntityWithComponentOfClass("CameraComponent");
        auto cameraComponent = std::static_pointer_cast<CameraComponent>(Engine::GetInstance().GetSingleComponentOfClass(cameraEntity, "CameraComponent"));
        cameraPosition = cameraComponent->GetPosition();
    }

    return cameraPosition;
}

float InputSystem::GetCameraHeight()
{
    float cameraHeight = 1;
    auto cameraEntities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("CameraComponent");

    if (cameraEntities.size() > 0)
    {
        auto cameraComponent = std::static_pointer_cast<CameraComponent>(Engine::GetInstance().GetSingleComponentOfClass(cameraEntities[0], "CameraComponent"));
        cameraHeight = cameraComponent->GetHeight();
    }

    return cameraHeight;
}

bool InputSystem::ProcessParticleForceInput()
{
    if (!Engine::GetInstance().CheckInputOccurred(InputType::MousePress))
        return false;
        
    if (!particleForceTimer.HasFired())
        return false;

    particleForceTimer.SetTime(CFG_GETF("INPUT_PERIOD"));

    Vector mousePosition = Engine::GetInstance().GetMousePosition();
    Vector worldPosition = ConvertWindowToWorldPosition(mousePosition);
    auto entities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("MoveableComponent");
    std::shared_ptr<MoveableComponent> moveableComponent;
    std::shared_ptr<ParticleComponent> particleComponent;
    Vector particlePosition;
    Vector inputForce;
    Vector resultantForce;
    float distance;

    LOG_I("[InputSystem] Applying force to particles");

    for (auto entity : entities)
    {
        moveableComponent = std::static_pointer_cast<MoveableComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "MoveableComponent"));
        particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "ParticleComponent"));

        if (moveableComponent->GetActive())
        {
            particlePosition = particleComponent->GetPosition();
            distance = particlePosition.CalculateDistance(worldPosition);
            inputForce = worldPosition - particlePosition;
            inputForce.Normalize();
            inputForce *= -CFG_GETF("INPUT_FORCE")/(1 + distance); // Summing with 1 to avoid division by zero.
            resultantForce = inputForce + particleComponent->GetForce();
            particleComponent->SetForce(resultantForce);
        }
    }

    return true;
}