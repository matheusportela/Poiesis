#include "poiesis/systems/RenderingSystem.h"

std::string RenderingSystem::GetName()
{
    return "RenderingSystem";
}

void RenderingSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[RenderingSystem] Update: " << dt);

    auto entities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("SpriteComponent");
    auto cameraEntities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("CameraComponent");
    std::shared_ptr<SpriteComponent> spriteComponent;
    std::shared_ptr<ParticleComponent> particleComponent;
    Vector position;
    std::string filename;
    Vector cameraOffset;

    if (cameraEntities.size() > 0)
    {
        auto cameraComponent = std::static_pointer_cast<CameraComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(cameraEntities[0], "CameraComponent"));
        Vector screenOffset = Vector(CFG_GETI("WINDOW_WIDTH"), CFG_GETI("WINDOW_HEIGHT"))*0.5;
        cameraOffset = cameraComponent->GetPosition() - screenOffset;
    }

    for (auto entity : entities)
    {
        spriteComponent = std::static_pointer_cast<SpriteComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "SpriteComponent"));
        particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "ParticleComponent"));
        filename = spriteComponent->GetFilename();

        if (!Engine::GetInstance().GetGraphicsAdapter()->IsLoaded(filename))
        {
            Engine::GetInstance().GetGraphicsAdapter()->LoadImage(filename);
            LOG_D("[RenderingSystem] Loaded image \"" << filename << "\" for entity with ID: " << entity->GetId());
        }

        position = particleComponent->GetPosition() - cameraOffset;

        if (spriteComponent->GetCentered())
            Engine::GetInstance().GetGraphicsAdapter()->RenderCenteredImage(filename, position.GetX(), position.GetY(), spriteComponent->GetScale());
        else
            Engine::GetInstance().GetGraphicsAdapter()->RenderImage(filename, position.GetX(), position.GetY(), spriteComponent->GetScale());
        LOG_D("[RenderingSystem] Rendered image \"" << filename << "\" for entity with ID: " << entity->GetId());
    }

    Engine::GetInstance().GetGraphicsAdapter()->RenderBatch();
}