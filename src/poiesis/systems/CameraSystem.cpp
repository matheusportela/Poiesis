#include "poiesis/systems/CameraSystem.h"

std::string CameraSystem::GetName()
{
    return "CameraSystem";
}

void CameraSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[CameraSystem] Update: " << dt);

    if (!Engine::GetInstance().HasEntityWithComponentOfClass("CameraComponent")
        || !Engine::GetInstance().HasEntityWithComponentOfClass("CameraFollowComponent"))
        return;

    auto camera = Engine::GetInstance().GetEntityWithComponentOfClass("CameraComponent");
    auto followEntity = Engine::GetInstance().GetEntityWithComponentOfClass("CameraFollowComponent");

    auto cameraComponent = std::static_pointer_cast<CameraComponent>(Engine::GetInstance().GetSingleComponentOfClass(camera, "CameraComponent"));
    auto cameraFollowComponent = std::static_pointer_cast<CameraFollowComponent>(Engine::GetInstance().GetSingleComponentOfClass(followEntity, "CameraFollowComponent"));
    auto particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetSingleComponentOfClass(followEntity, "ParticleComponent"));

    if (!cameraFollowComponent->GetEnabled())
        return;


    auto particlePosition = particleComponent->GetPosition();
    auto cameraPosition = cameraComponent->GetPosition();

    if (cameraPosition.CalculateDistance(particlePosition) > CFG_GETF("CAMERA_MAX_DISTANCE"))
    {
        auto exceeding = particlePosition - cameraPosition;
        auto mag = exceeding.GetMagnitude();
        auto dir = exceeding.GetDirection();
        exceeding.SetPolar(mag - CFG_GETF("CAMERA_MAX_DISTANCE"), dir);
        cameraPosition += exceeding;
    }

    cameraComponent->SetPosition(cameraPosition);
}