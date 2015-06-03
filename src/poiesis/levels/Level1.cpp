#include "poiesis/levels/Level1.h"

void Level1::Start()
{
    LOG_I("[Level1] Starting");
    
    Random r;
    float x;
    float y;

    EntityFactory::CreateBackground();
    EntityFactory::CreateCamera();

    // Creating areas.
    for (int i = 0; i < CFG_GETI("LEVEL_1_NUM_SLOW_AREAS"); ++i)
    {
        x = r.GenerateFloat(-2000, 2000);
        y = r.GenerateFloat(-2000, 2000);
        EntityFactory::CreateSlowArea(Vector(x, y));
    }

    for (int i = 0; i < CFG_GETI("LEVEL_1_NUM_FAST_AREAS"); ++i)
    {
        x = r.GenerateFloat(-2000, 2000);
        y = r.GenerateFloat(-2000, 2000);
        EntityFactory::CreateFastArea(Vector(x, y));
    }

    // Cells and food must be created after areas to be rendered above them.
    EntityFactory::CreatePlayer();

    for (int i = 0; i < CFG_GETI("LEVEL_1_INITIAL_NUM_CELLS"); ++i)
    {
        x = r.GenerateFloat(-2000, 2000);
        y = r.GenerateFloat(-2000, 2000);
        EntityFactory::CreateCell(1, Vector(x, y));
    }

    for (int i = 0; i < CFG_GETI("LEVEL_1_INITIAL_NUM_FOOD"); ++i)
    {
        x = r.GenerateFloat(-2000, 2000);
        y = r.GenerateFloat(-2000, 2000);
        EntityFactory::CreateFood(Vector(x, y));
    }

    // Creating systems.
    Engine::GetInstance().AddSystem(std::make_shared<CellSpawningSystem>());
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

    auto followEntities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("CameraFollowComponent");

    if (followEntities.size() == 0)
    {
        win = false;
        SetFinished();
    }
    else
    {
        auto growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(followEntities[0], "GrowthComponent"));

        if (growthComponent->GetLevel() == CFG_GETI("LEVEL_1_GOAL_SIZE"))
        {
            win = true;
            SetFinished();
        }
    }
}

void Level1::Finish()
{
    LOG_I("[Level1] Finishing");

    if (win)
    {
        Engine::GetInstance().GetGraphicsAdapter()->Write("You win",
        CFG_GETP("FONT_FILE"), CFG_GETI("WINDOW_WIDTH")/2,
        CFG_GETI("WINDOW_HEIGHT")/2);
    }
    else
    {
        Engine::GetInstance().GetGraphicsAdapter()->Write("You lost",
        CFG_GETP("FONT_FILE"), CFG_GETI("WINDOW_WIDTH")/2,
        CFG_GETI("WINDOW_HEIGHT")/2);
    }
}