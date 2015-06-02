#include "poiesis/levels/Level1.h"

void Level1::Start()
{
    LOG_I("[Level1] Starting");
    
    Random r;
    float x;
    float y;

    EntityFactory::CreateBackground();
    EntityFactory::CreateCamera();

    for (int i = 0; i < 10; ++i)
    {
        x = r.GenerateFloat(-2000, 2000);
        y = r.GenerateFloat(-2000, 2000);
        EntityFactory::CreateSlowArea(Vector(x, y));

        x = r.GenerateFloat(-2000, 2000);
        y = r.GenerateFloat(-2000, 2000);
        EntityFactory::CreateFastArea(Vector(x, y));
    }

    EntityFactory::CreatePlayer();
    EntityFactory::CreateCell(1, Vector(410, 310));
    EntityFactory::CreateFood(Vector(700, 300));

    
    for (int i = 0; i < 50; ++i)
    {
        x = r.GenerateFloat(-2000, 2000);
        y = r.GenerateFloat(-2000, 2000);
        EntityFactory::CreateCell(1, Vector(x, y));
    }

    Engine::GetInstance().AddSystem(std::make_shared<FoodSpawningSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<GrowthSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<InputSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<CollisionSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<ParticleSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<CameraSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<DebugSystem>());
}

void Level1::Update()
{
    LOG_D("[Level1] Updating");
}

void Level1::Finish()
{
    LOG_I("[Level1] Finishing");
}