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
    Vector cameraPosition;
    Vector cameraOffset;

    if (cameraEntities.size() > 0)
    {
        auto cameraComponent = std::static_pointer_cast<CameraComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(cameraEntities[0], "CameraComponent"));
        Vector screenOffset = Vector(CFG_GETI("WINDOW_WIDTH"), CFG_GETI("WINDOW_HEIGHT"))*0.5;
        cameraPosition = cameraComponent->GetPosition();
        cameraOffset = cameraPosition - screenOffset;
    }

    Engine::GetInstance().GetGraphicsAdapter()->InitRendering();

    for (auto entity : entities)
    {
        auto spriteComponents = Engine::GetInstance().GetEntityManager()->GetComponentsOfClass(entity, "SpriteComponent");
        particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "ParticleComponent"));

        for (auto component : spriteComponents)
        {
            spriteComponent = std::static_pointer_cast<SpriteComponent>(component);
            filename = spriteComponent->GetFilename();

            // Skip rendering entities that are too far from the screen.
            if (particleComponent->GetPosition().CalculateDistance(cameraPosition) > CFG_GETF("RENDERING_MAX_DISTANCE"))
                continue;

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
    }

    Engine::GetInstance().GetGraphicsAdapter()->FinishRendering();
}