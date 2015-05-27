#include "poiesis/EntityFactory.h"

std::shared_ptr<Entity> EntityFactory::CreateBackground()
{
    std::shared_ptr<Entity> background = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(CFG_GETP("BACKGROUND_IMAGE"), false),
        background);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(), background);
    return background;
}

std::shared_ptr<Entity> EntityFactory::CreateCell(float inverseMass,
    Vector position)
{
    std::shared_ptr<Entity> cell = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>(CFG_GETP("CELL_IMAGE")), cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<MoveableComponent>(), cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(inverseMass, position, Vector(0, 0),
            Vector(0, 0), CFG_GETF("CELL_DAMPING")), cell);
    Engine::GetInstance().AddComponent(
        std::make_shared<GrowthComponent>(), cell);
    return cell;
}