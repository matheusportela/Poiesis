#include "poiesis/systems/CameraSystem.h"

std::string CameraSystem::GetName()
{
    return "CameraSystem";
}

void CameraSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[CameraSystem] Update: " << dt);

    auto cameraEntities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("CameraComponent");
    auto followEntities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("CameraFollowComponent");

    if (cameraEntities.size() == 0 || followEntities.size() == 0)
        return;

    auto camera = cameraEntities[0];
    auto followEntity = followEntities[0];

    auto cameraComponent = std::static_pointer_cast<CameraComponent>(Engine::GetInstance().GetSingleComponentOfClass(camera, "CameraComponent"));
    auto cameraFollowComponent = std::static_pointer_cast<CameraFollowComponent>(Engine::GetInstance().GetSingleComponentOfClass(followEntity, "CameraFollowComponent"));
    auto particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetSingleComponentOfClass(followEntity, "ParticleComponent"));

    if (cameraFollowComponent->GetEnabled())
        cameraComponent->SetPosition(particleComponent->GetPosition());
}