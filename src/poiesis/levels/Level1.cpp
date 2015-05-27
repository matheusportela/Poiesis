#include "poiesis/levels/Level1.h"

void Level1::Start()
{
    LOG_I("[Level1] Starting");
    std::shared_ptr<Entity> windowEntity = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>("resources/img/black.png"), windowEntity);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(), windowEntity);

    std::shared_ptr<Entity> playerEntity = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>("resources/img/cell.png"), playerEntity);
    Engine::GetInstance().AddComponent(
        std::make_shared<MoveableComponent>(), playerEntity);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(1, Vector(100, 200), Vector(0, 0), Vector(0, 0), 0.9), playerEntity);

    playerEntity = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>("resources/img/cell.png"), playerEntity);
    Engine::GetInstance().AddComponent(
        std::make_shared<MoveableComponent>(), playerEntity);
    Engine::GetInstance().AddComponent(
        std::make_shared<ParticleComponent>(1, Vector(400, 300), Vector(0, 0), Vector(0, 0), 0.9), playerEntity);

    Engine::GetInstance().AddSystem(std::make_shared<InputSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<ParticleSystem>());
}

void Level1::Update()
{
    LOG_D("[Level1] Updating");
    SetFinished();
}

void Level1::Finish()
{
    LOG_I("[Level1] Finishing");
}