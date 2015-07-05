#include "poiesis/levels/Level1.h"

void Level1::Start()
{
    LOG_I("[Level1] Starting");
    
    Random r;
    float x;
    float y;
    int type;

    EntityFactory::CreateBackground();
    EntityFactory::CreateCamera();

    EntityFactory::CreateButton(CFG_GETP("MENU_BUTTON_IMAGE"),
        Rectangle(1700, 10, 150, 50),
        std::bind(&Level1::MenuButtonCallback, this));

    EntityFactory::CreateButton(CFG_GETP("PAUSE_BUTTON_IMAGE"),
        Rectangle(1700, 110, 150, 50),
        std::bind(&Level1::PauseButtonCallback, this));

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

    for (int i = 0; i < CFG_GETI("LEVEL_1_NUM_VITAMIN_AREAS"); ++i)
    {
        x = r.GenerateFloat(-2000, 2000);
        y = r.GenerateFloat(-2000, 2000);
        EntityFactory::CreateVitaminArea(Vector(x, y));
    }

    for (int i = 0; i < CFG_GETI("LEVEL_1_NUM_ACID_AREAS"); ++i)
    {
        x = r.GenerateFloat(-2000, 2000);
        y = r.GenerateFloat(-2000, 2000);
        EntityFactory::CreateAcidArea(Vector(x, y));
    }

    // Cells and food must be created after areas to be rendered above them.
    EntityFactory::CreatePlayer();

    for (int i = 0; i < CFG_GETI("LEVEL_1_INITIAL_NUM_CELLS"); ++i)
    {
        x = r.GenerateFloat(-2000, 2000);
        y = r.GenerateFloat(-2000, 2000);
        type = r.GenerateInt(1, 6);
        EntityFactory::CreateCell(type, Vector(x, y));
    }

    for (int i = 0; i < CFG_GETI("LEVEL_1_INITIAL_NUM_FOOD"); ++i)
    {
        x = r.GenerateFloat(-2000, 2000);
        y = r.GenerateFloat(-2000, 2000);
        EntityFactory::CreateFood(Vector(x, y));
    }

    for (int i = 0; i < CFG_GETI("LEVEL_1_INITIAL_NUM_VIRUSES"); ++i)
    {
        x = r.GenerateFloat(-2000, 2000);
        y = r.GenerateFloat(-2000, 2000);
        EntityFactory::CreateVirus(Vector(x, y));
    }

    // Creating systems.
    CreateAllSystems();
}

void Level1::CreateAllSystems()
{
    CreateEssentialSystems();
    CreateAccessorySystems();
}

void Level1::CreateEssentialSystems()
{
    Engine::GetInstance().AddSystem(std::make_shared<RenderingSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<InputSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<DebugSystem>());
}

void Level1::CreateAccessorySystems()
{
    Engine::GetInstance().AddSystem(std::make_shared<CellSpawningSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<FoodSpawningSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<GrowthSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<CombatPowerSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<AISystem>());
    Engine::GetInstance().AddSystem(std::make_shared<CollisionSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<ParticleSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<CameraSystem>());
}

void Level1::DeleteAccessorySystems()
{
    Engine::GetInstance().DeleteSystem("CellSpawningSystem");
    Engine::GetInstance().DeleteSystem("FoodSpawningSystem");
    Engine::GetInstance().DeleteSystem("GrowthSystem");
    Engine::GetInstance().DeleteSystem("CombatPowerSystem");
    Engine::GetInstance().DeleteSystem("AISystem");
    Engine::GetInstance().DeleteSystem("CollisionSystem");
    Engine::GetInstance().DeleteSystem("ParticleSystem");
    Engine::GetInstance().DeleteSystem("CameraSystem");
}

void Level1::Update()
{
    LOG_D("[Level1] Updating");

    auto playerEntities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("PlayerComponent");

    if (playerEntities.size() == 0)
    {
        Engine::GetInstance().SetNextLevel(std::make_shared<LoseLevel>());
        SetFinished();
    }
    else
    {
        auto growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(playerEntities[0], "GrowthComponent"));

        if (growthComponent->GetLevel() == CFG_GETI("LEVEL_1_GOAL_SIZE"))
        {
            Engine::GetInstance().SetNextLevel(std::make_shared<WinLevel>());
            SetFinished();
        }
    }
}

void Level1::Finish()
{
    LOG_I("[Level1] Finishing");

    Engine::GetInstance().ClearEntities();
    Engine::GetInstance().ClearSystems();
}

void Level1::MenuButtonCallback()
{
    LOG_I("[Level1] Clicked on menu button");
    SetFinished();
    Engine::GetInstance().SetNextLevel(std::make_shared<EntryLevel>());
}

void Level1::PauseButtonCallback()
{
    LOG_I("[Level1] Clicked on pause button");

    if (paused)
    {
        paused = false;
        CreateAccessorySystems();
        Engine::GetInstance().DeleteEntity(pauseMenuExitButton);
    }
    else
    {
        paused = true;
        DeleteAccessorySystems();
        pauseMenuExitButton = EntityFactory::CreateButton(
            CFG_GETP("EXIT_BUTTON_IMAGE"), Rectangle(800, 500, 150, 50),
            std::bind(&Level1::ExitButtonCallback, this));
    }
}

void Level1::ExitButtonCallback()
{
    LOG_I("[Level1] Clicked on exit button");
    SetFinished();
}