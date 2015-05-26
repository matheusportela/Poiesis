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
    std::shared_ptr<PositionComponent> positionComponent;

    for (auto entity : entities)
    {
        spriteComponent = std::static_pointer_cast<SpriteComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "SpriteComponent"));
        positionComponent = std::static_pointer_cast<PositionComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "PositionComponent"));
        
        if (!Engine::GetInstance().GetGraphicsAdapter()->IsLoaded(spriteComponent->filename))
        {
            Engine::GetInstance().GetGraphicsAdapter()->LoadImage(spriteComponent->filename);
            LOG_D("[RenderingSystem] Loaded image \"" << spriteComponent->filename << "\" for entity with ID: " << entity->GetId());
        }

        Engine::GetInstance().GetGraphicsAdapter()->RenderImage(spriteComponent->filename, positionComponent->x, positionComponent->y);
        LOG_D("[RenderingSystem] Rendered image \"" << spriteComponent->filename << "\" for entity with ID: " << entity->GetId());
    }
}