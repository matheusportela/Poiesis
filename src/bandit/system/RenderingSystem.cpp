#include "bandit/system/RenderingSystem.h"

RenderingSystem::RenderingSystem(std::shared_ptr<EntityManager> entityManager,
    std::shared_ptr<GraphicsAdapter> graphicsAdapter,
    std::shared_ptr<InputAdapter> inputAdapter) :
    System(entityManager), graphicsAdapter(graphicsAdapter),
    inputAdapter(inputAdapter)
{
}

std::string RenderingSystem::GetName()
{
    return "RenderingSystem";
}

std::string RenderingSystem::GetComponentClass()
{
    return "SpriteComponent";
}

void RenderingSystem::ProcessEntityComponent(std::shared_ptr<Entity> entity,
    std::shared_ptr<Component> component)
{
    std::shared_ptr<SpriteComponent> spriteComponent =
        std::static_pointer_cast<SpriteComponent>(component);

    if (!graphicsAdapter->IsLoaded(spriteComponent->filename))
    {
        graphicsAdapter->LoadImage(spriteComponent->filename);
        LOG_D("[RenderingSystem] Loaded image \"" << spriteComponent->filename
            << "\" for entity with ID: " << entity->GetId());
    }

    graphicsAdapter->RenderImage(spriteComponent->filename,
        spriteComponent->x, spriteComponent->y);
    LOG_D("[RenderingSystem] Rendered image \"" << spriteComponent->filename
            << "\" for entity with ID: " << entity->GetId());

    // spriteComponent->x += 10;
    // spriteComponent->y += 10;

    if (inputAdapter->CheckInputOccurred(InputType::MousePress))
        LOG_I("Mouse pressed");
}

void RenderingSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[RenderingSystem] Update: " << dt);

    std::string componentClass = GetComponentClass();
    std::vector<std::shared_ptr<Entity>> entities =
        entityManager->GetAllEntitiesWithComponentOfClass(componentClass);
    std::vector<std::shared_ptr<Component>> components;

    for (std::shared_ptr<Entity> entity : entities)
    {
        components = entityManager->GetComponentsOfClass(entity, componentClass);
        for (std::shared_ptr<Component> component : components)
        {
            ProcessEntityComponent(entity, component);
        }
    }
}