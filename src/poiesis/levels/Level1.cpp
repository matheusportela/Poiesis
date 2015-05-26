#include "poiesis/levels/Level1.h"

void Level1::Start()
{
    LOG_I("[Level1] Starting");
    std::shared_ptr<Entity> windowEntity = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>("resources/img/black.png"), windowEntity);
    Engine::GetInstance().AddComponent(
        std::make_shared<PositionComponent>(0, 0), windowEntity);

    std::shared_ptr<Entity> playerEntity = Engine::GetInstance().CreateEntity();
    Engine::GetInstance().AddComponent(
        std::make_shared<SpriteComponent>("resources/img/penguin.png"), playerEntity);
    Engine::GetInstance().AddComponent(
        std::make_shared<PositionComponent>(100, 200), playerEntity);

    Engine::GetInstance().AddSystem(std::make_shared<PlayerMovementSystem>());
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