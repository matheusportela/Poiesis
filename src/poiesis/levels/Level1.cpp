#include "poiesis/levels/Level1.h"

void Level1::Start()
{
    LOG_I("[Level1] Starting");
    
    CreateAllEntities();
    CreateAllSystems();
}

void Level1::CreateAllEntities()
{
    EntityFactory::CreateBackground();
    EntityFactory::CreateCamera(CFG_GETF("LEVEL_1_CAMERA_HEIGHT"));

    CreateButtons();
    CreateAreas();

    // Cells and food must be created after areas to be rendered above them.
    auto player = EntityFactory::CreatePlayer();
    Engine::GetInstance().AddComponent(
        std::make_shared<AIComponent>("EatableComponent"), player);

    CreateCells();
    CreateFood();
    CreateViruses();
}

void Level1::CreateButtons()
{
    EntityFactory::CreateButton(CFG_GETP("MENU_BUTTON_IMAGE"),
        Rectangle(CFG_GETF("LEVEL_COMMON_MENU_BUTTON_X"),
            CFG_GETF("LEVEL_COMMON_MENU_BUTTON_Y"),
            CFG_GETF("LEVEL_COMMON_MENU_BUTTON_WIDTH"),
            CFG_GETF("LEVEL_COMMON_MENU_BUTTON_HEIGHT")),
        std::bind(&Level1::MenuButtonCallback, this));

    EntityFactory::CreateButton(CFG_GETP("PAUSE_BUTTON_IMAGE"),
        Rectangle(CFG_GETF("LEVEL_COMMON_PAUSE_BUTTON_X"),
            CFG_GETF("LEVEL_COMMON_PAUSE_BUTTON_Y"),
            CFG_GETF("LEVEL_COMMON_PAUSE_BUTTON_WIDTH"),
            CFG_GETF("LEVEL_COMMON_PAUSE_BUTTON_HEIGHT")),
        std::bind(&Level1::PauseButtonCallback, this));
}

void Level1::CreateAreas()
{
    Random r;
    float x;
    float y;

    for (int i = 0; i < CFG_GETI("LEVEL_1_NUM_SLOW_AREAS"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_1_MIN_X"), CFG_GETF("LEVEL_1_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_1_MIN_Y"), CFG_GETF("LEVEL_1_MAX_Y"));
        EntityFactory::CreateSlowArea(Vector(x, y));
    }

    for (int i = 0; i < CFG_GETI("LEVEL_1_NUM_FAST_AREAS"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_1_MIN_X"), CFG_GETF("LEVEL_1_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_1_MIN_Y"), CFG_GETF("LEVEL_1_MAX_Y"));
        EntityFactory::CreateFastArea(Vector(x, y));
    }

    for (int i = 0; i < CFG_GETI("LEVEL_1_NUM_VITAMIN_AREAS"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_1_MIN_X"), CFG_GETF("LEVEL_1_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_1_MIN_Y"), CFG_GETF("LEVEL_1_MAX_Y"));
        EntityFactory::CreateVitaminArea(Vector(x, y));
    }

    for (int i = 0; i < CFG_GETI("LEVEL_1_NUM_ACID_AREAS"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_1_MIN_X"), CFG_GETF("LEVEL_1_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_1_MIN_Y"), CFG_GETF("LEVEL_1_MAX_Y"));
        EntityFactory::CreateAcidArea(Vector(x, y));
    }
}

void Level1::CreateCells()
{
    Random r;
    float x;
    float y;
    std::shared_ptr<Entity> cell;

    for (int i = 0; i < CFG_GETI("LEVEL_1_INITIAL_NUM_CELLS"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_1_MIN_X"), CFG_GETF("LEVEL_1_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_1_MIN_Y"), CFG_GETF("LEVEL_1_MAX_Y"));
        cell = EntityFactory::CreateRandomCell(Vector(x, y));
        Engine::GetInstance().AddComponent(
            std::make_shared<AIComponent>("EatableComponent"), cell);
    }
}

void Level1::CreateFood()
{
    Random r;
    float x;
    float y;

    for (int i = 0; i < CFG_GETI("LEVEL_1_INITIAL_NUM_FOOD"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_1_MIN_X"), CFG_GETF("LEVEL_1_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_1_MIN_Y"), CFG_GETF("LEVEL_1_MAX_Y"));
        EntityFactory::CreateFood(Vector(x, y));
    }
}

void Level1::CreateViruses()
{
    Random r;
    float x;
    float y;

    for (int i = 0; i < CFG_GETI("LEVEL_1_INITIAL_NUM_VIRUSES"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_1_MIN_X"), CFG_GETF("LEVEL_1_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_1_MIN_Y"), CFG_GETF("LEVEL_1_MAX_Y"));
        EntityFactory::CreateVirus(Vector(x, y));
    }
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
    Engine::GetInstance().AddSystem(std::make_shared<SpawningSystem>(
            CellSpawning,
            CFG_GETF("CELL_SPAWNING_CHANCE"),
            CFG_GETF("CELL_SPAWNING_PERIOD")));
    Engine::GetInstance().AddSystem(std::make_shared<SpawningSystem>(
            FoodSpawning,
            CFG_GETF("FOOD_SPAWNING_CHANCE"),
            CFG_GETF("FOOD_SPAWNING_PERIOD")));
    Engine::GetInstance().AddSystem(std::make_shared<GrowthSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<CombatPowerSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<AISystem>());
    Engine::GetInstance().AddSystem(std::make_shared<CollisionSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<ParticleSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<CameraSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<AnimationSystem>());
}

void Level1::DeleteAccessorySystems()
{
    Engine::GetInstance().DeleteSystem("SpawningSystem");
    Engine::GetInstance().DeleteSystem("GrowthSystem");
    Engine::GetInstance().DeleteSystem("CombatPowerSystem");
    Engine::GetInstance().DeleteSystem("AISystem");
    Engine::GetInstance().DeleteSystem("CollisionSystem");
    Engine::GetInstance().DeleteSystem("ParticleSystem");
    Engine::GetInstance().DeleteSystem("CameraSystem");
    Engine::GetInstance().DeleteSystem("AnimationSystem");
}

void Level1::Update()
{
    LOG_D("[Level1] Updating");

    if (!Engine::GetInstance().HasEntityWithComponentOfClass("PlayerComponent"))
    {
        Engine::GetInstance().SetNextLevel(std::make_shared<LoseLevel>());
        SetFinished();
    }
    else
    {
        auto playerEntity = Engine::GetInstance().GetEntityWithComponentOfClass("PlayerComponent");
        auto growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(playerEntity, "GrowthComponent"));

        if (growthComponent->GetLevel() == CFG_GETI("LEVEL_1_GOAL_SIZE"))
        {
            Engine::GetInstance().SetNextLevel(std::make_shared<Level2>());
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
            CFG_GETP("EXIT_BUTTON_IMAGE"),
            Rectangle(CFG_GETF("LEVEL_COMMON_PAUSE_MENU_EXIT_BUTTON_X"),
                CFG_GETF("LEVEL_COMMON_PAUSE_MENU_EXIT_BUTTON_Y"),
                CFG_GETF("LEVEL_COMMON_PAUSE_MENU_EXIT_BUTTON_WIDTH"),
                CFG_GETF("LEVEL_COMMON_PAUSE_MENU_EXIT_BUTTON_HEIGHT")),
            std::bind(&Level1::ExitButtonCallback, this));
    }
}

void Level1::ExitButtonCallback()
{
    LOG_I("[Level1] Clicked on exit button");
    SetFinished();
}