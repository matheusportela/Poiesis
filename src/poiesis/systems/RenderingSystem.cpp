#include "poiesis/systems/RenderingSystem.h"

std::string RenderingSystem::GetName()
{
    return "RenderingSystem";
}

void RenderingSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[RenderingSystem] Update: " << dt);

    auto entities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("SpriteComponent");
    Vector cameraOffset = CalculateCameraOffset();
    Vector cameraPosition = cameraOffset + CalculateScreenOffset();
    float cameraHeight = GetCameraHeight();

    Engine::GetInstance().GetGraphicsAdapter()->InitRendering();

    for (auto entity : entities)
    {
        if (Engine::GetInstance().HasComponent(entity, "ButtonComponent"))
        {
            RenderGUI(entity);
        }
        else if (Engine::GetInstance().HasComponent(entity, "ParticleComponent"))
        {
            RenderParticle(entity, cameraPosition, cameraHeight);
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
    auto cameraEntities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("CameraComponent");

    if (cameraEntities.size() > 0)
    {
        auto cameraComponent = std::static_pointer_cast<CameraComponent>(Engine::GetInstance().GetSingleComponentOfClass(cameraEntities[0], "CameraComponent"));
        Vector screenOffset = CalculateScreenOffset();
        cameraOffset = cameraComponent->GetPosition() - screenOffset;
    }

    return cameraOffset;
}

float RenderingSystem::GetCameraHeight()
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

void RenderingSystem::RenderParticle(std::shared_ptr<Entity> entity, Vector cameraPosition, float cameraHeight)
{
    Vector position;
    std::shared_ptr<SpriteComponent> spriteComponent;
    auto spriteComponents = Engine::GetInstance().GetComponentsOfClass(entity, "SpriteComponent");
    auto particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "ParticleComponent"));
            
    // Skip rendering entities that are too far from the screen.
    if (particleComponent->GetPosition().CalculateDistance(cameraPosition) > CFG_GETF("RENDERING_MAX_DISTANCE"))
        return;

    for (auto component : spriteComponents)
    {
        spriteComponent = std::static_pointer_cast<SpriteComponent>(component);
        position = CalculateScreenOffset() - (cameraPosition - (spriteComponent->GetPosition() + particleComponent->GetPosition()))*(1/cameraHeight);
        RenderSprite(entity, spriteComponent, position, cameraHeight);
    }
}

void RenderingSystem::RenderGUI(std::shared_ptr<Entity> entity)
{
    Vector position;
    std::shared_ptr<SpriteComponent> spriteComponent;
    auto spriteComponents = Engine::GetInstance().GetComponentsOfClass(entity, "SpriteComponent");
    std::shared_ptr<ButtonComponent> buttonComponent = std::static_pointer_cast<ButtonComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "ButtonComponent"));

    for (auto component : spriteComponents)
    {
        spriteComponent = std::static_pointer_cast<SpriteComponent>(component);
        position = spriteComponent->GetPosition() + buttonComponent->GetRectangle().GetCenter();
        RenderSprite(entity, spriteComponent, position);
    }
}

void RenderingSystem::RenderSprite(std::shared_ptr<Entity> entity, std::shared_ptr<SpriteComponent> spriteComponent, Vector position, float height)
{
    std::string filename = spriteComponent->GetFilename();

    if (!Engine::GetInstance().GetGraphicsAdapter()->IsLoaded(filename))
    {
        Engine::GetInstance().GetGraphicsAdapter()->LoadImage(filename);
        LOG_D("[RenderingSystem] Loaded image \"" << filename << "\" for entity with ID: " << entity->GetId());
    }

    if (spriteComponent->GetCentered())
        Engine::GetInstance().GetGraphicsAdapter()->RenderCenteredImage(filename, position.GetX(), position.GetY(), spriteComponent->GetRotation(), spriteComponent->GetScale()/height, spriteComponent->GetCurrentFrame(), spriteComponent->GetNumFrames());
    else
        Engine::GetInstance().GetGraphicsAdapter()->RenderImage(filename, position.GetX(), position.GetY(), spriteComponent->GetRotation(), spriteComponent->GetScale()/height, spriteComponent->GetCurrentFrame(), spriteComponent->GetNumFrames());
    LOG_D("[RenderingSystem] Rendered image \"" << filename << "\" for entity with ID: " << entity->GetId());
}