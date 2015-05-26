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
    std::shared_ptr<SpriteComponent> spriteComponent;
    std::shared_ptr<ParticleComponent> particleComponent;
    Vector position;

    for (auto entity : entities)
    {
        spriteComponent = std::static_pointer_cast<SpriteComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "SpriteComponent"));
        particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "ParticleComponent"));
        
        if (!Engine::GetInstance().GetGraphicsAdapter()->IsLoaded(spriteComponent->filename))
        {
            Engine::GetInstance().GetGraphicsAdapter()->LoadImage(spriteComponent->filename);
            LOG_D("[RenderingSystem] Loaded image \"" << spriteComponent->filename << "\" for entity with ID: " << entity->GetId());
        }

        position = particleComponent->GetPosition();
        Engine::GetInstance().GetGraphicsAdapter()->RenderImage(spriteComponent->filename, position.GetX(), position.GetY());
        LOG_D("[RenderingSystem] Rendered image \"" << spriteComponent->filename << "\" for entity with ID: " << entity->GetId());
    }
}