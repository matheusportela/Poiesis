#include "poiesis/level/Level1.h"

void Level1::Start()
{
    LOG_I("[Level1] Starting");
    std::shared_ptr<EntityManager> entityManager = Engine::GetInstance().GetEntityManager();

    std::shared_ptr<Entity> windowEntity = entityManager->CreateEntity();
    entityManager->AddComponent(
        std::make_shared<SpriteComponent>("resources/img/black.png"),
                                          windowEntity);

    std::shared_ptr<Entity> playerEntity = entityManager->CreateEntity();
    entityManager->AddComponent(
        std::make_shared<SpriteComponent>("resources/img/penguin.png"),
                                          playerEntity);
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