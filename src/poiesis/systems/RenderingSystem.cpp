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
    std::shared_ptr<ButtonComponent> buttonComponent;
    Vector position;
    Vector cameraOffset = CalculateCameraOffset();
    Vector cameraPosition = cameraOffset + CalculateScreenOffset();

    Engine::GetInstance().GetGraphicsAdapter()->InitRendering();

    for (auto entity : entities)
    {
        if (Engine::GetInstance().GetEntityManager()->HasComponent(entity, "ButtonComponent"))
        {
            RenderGUI(entity);
        }
        else if (Engine::GetInstance().GetEntityManager()->HasComponent(entity, "ParticleComponent"))
        {
            RenderParticle(entity, cameraOffset, cameraPosition);
        }
        else
        {
            LOG_E("[RenderingSystem] Entity " << entity->GetId() << " contains sprite without positioning components.");
            exit(1);
        }
    }

    Engine::GetInstance().GetGraphicsAdapter()->FinishRendering();
}

Vector RenderingSystem::CalculateScreenOffset()
{
    return Vector(CFG_GETI("WINDOW_WIDTH"), CFG_GETI("WINDOW_HEIGHT"))*0.5;
}

Vector RenderingSystem::CalculateCameraOffset()
{
    Vector cameraOffset;
    auto cameraEntities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("CameraComponent");

    if (cameraEntities.size() > 0)
    {
        auto cameraComponent = std::static_pointer_cast<CameraComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(cameraEntities[0], "CameraComponent"));
        Vector screenOffset = CalculateScreenOffset();
        cameraOffset = cameraComponent->GetPosition() - screenOffset;
    }

    return cameraOffset;
}

void RenderingSystem::RenderParticle(std::shared_ptr<Entity> entity, Vector cameraOffset, Vector cameraPosition)
{
    Vector position;
    std::shared_ptr<SpriteComponent> spriteComponent;
    auto spriteComponents = Engine::GetInstance().GetEntityManager()->GetComponentsOfClass(entity, "SpriteComponent");
    auto particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "ParticleComponent"));
            
    // Skip rendering entities that are too far from the screen.
    if (particleComponent->GetPosition().CalculateDistance(cameraPosition) > CFG_GETF("RENDERING_MAX_DISTANCE"))
        return;

    for (auto component : spriteComponents)
    {
        spriteComponent = std::static_pointer_cast<SpriteComponent>(component);
        position = spriteComponent->GetPosition() + particleComponent->GetPosition() - cameraOffset;
        RenderSprite(entity, spriteComponent, position);
    }
}

void RenderingSystem::RenderGUI(std::shared_ptr<Entity> entity)
{
    Vector position;
    std::shared_ptr<SpriteComponent> spriteComponent;
    auto spriteComponents = Engine::GetInstance().GetEntityManager()->GetComponentsOfClass(entity, "SpriteComponent");
    std::shared_ptr<ButtonComponent> buttonComponent = std::static_pointer_cast<ButtonComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "ButtonComponent"));

    for (auto component : spriteComponents)
    {
        spriteComponent = std::static_pointer_cast<SpriteComponent>(component);
        position = spriteComponent->GetPosition() + buttonComponent->GetRectangle().GetCenter();
        RenderSprite(entity, spriteComponent, position);
    }
}

void RenderingSystem::RenderSprite(std::shared_ptr<Entity> entity, std::shared_ptr<SpriteComponent> spriteComponent, Vector position)
{
    std::string filename = spriteComponent->GetFilename();

    if (!Engine::GetInstance().GetGraphicsAdapter()->IsLoaded(filename))
    {
        Engine::GetInstance().GetGraphicsAdapter()->LoadImage(filename);
        LOG_D("[RenderingSystem] Loaded image \"" << filename << "\" for entity with ID: " << entity->GetId());
    }

    if (spriteComponent->GetCentered())
        Engine::GetInstance().GetGraphicsAdapter()->RenderCenteredImage(filename, position.GetX(), position.GetY(), spriteComponent->GetScale());
    else
        Engine::GetInstance().GetGraphicsAdapter()->RenderImage(filename, position.GetX(), position.GetY(), spriteComponent->GetScale());
    LOG_D("[RenderingSystem] Rendered image \"" << filename << "\" for entity with ID: " << entity->GetId());
}