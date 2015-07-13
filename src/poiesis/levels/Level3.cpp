#include "poiesis/levels/Level3.h"

void Level3::Start()
{
    LOG_I("[Level3] Starting");
    
    CreateAllEntities();
    CreateAllSystems();
}

void Level3::CreateAllEntities()
{
    // EntityFactory::CreateBackground();
    EntityFactory::CreateCamera(CFG_GETF("LEVEL_3_CAMERA_HEIGHT"));

    CreateButtons();

    // Cells and food must be created after areas to be rendered above them.
    EntityFactory::CreatePlayer();

    // CreateCells();
    CreateBacteria();
}

void Level3::CreateButtons()
{
    EntityFactory::CreateButton(CFG_GETP("MENU_BUTTON_IMAGE"),
        Rectangle(CFG_GETF("LEVEL_COMMON_MENU_BUTTON_X"),
            CFG_GETF("LEVEL_COMMON_MENU_BUTTON_Y"),
            CFG_GETF("LEVEL_COMMON_MENU_BUTTON_WIDTH"),
            CFG_GETF("LEVEL_COMMON_MENU_BUTTON_HEIGHT")),
        std::bind(&Level3::MenuButtonCallback, this));

    EntityFactory::CreateButton(CFG_GETP("PAUSE_BUTTON_IMAGE"),
        Rectangle(CFG_GETF("LEVEL_COMMON_PAUSE_BUTTON_X"),
            CFG_GETF("LEVEL_COMMON_PAUSE_BUTTON_Y"),
            CFG_GETF("LEVEL_COMMON_PAUSE_BUTTON_WIDTH"),
            CFG_GETF("LEVEL_COMMON_PAUSE_BUTTON_HEIGHT")),
        std::bind(&Level3::PauseButtonCallback, this));
}

void Level3::CreateCells()
{
    Random r;
    float x;
    float y;

    for (int i = 0; i < CFG_GETI("LEVEL_3_INITIAL_NUM_CELLS"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_3_MIN_X"), CFG_GETF("LEVEL_3_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_3_MIN_Y"), CFG_GETF("LEVEL_3_MAX_Y"));
        EntityFactory::CreateCell(Vector(x, y));
    }
}

void Level3::CreateBacteria()
{
    Random r;
    float x;
    float y;

    for (int i = 0; i < CFG_GETI("LEVEL_3_INITIAL_NUM_CELLS"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_3_MIN_X"), CFG_GETF("LEVEL_3_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_3_MIN_Y"), CFG_GETF("LEVEL_3_MAX_Y"));
        EntityFactory::CreateBacterium(Vector(x, y));
    }
}

void Level3::CreateAllSystems()
{
    CreateEssentialSystems();
    CreateAccessorySystems();
}

void Level3::CreateEssentialSystems()
{
    Engine::GetInstance().AddSystem(std::make_shared<RenderingSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<InputSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<DebugSystem>());
}

void Level3::CreateAccessorySystems()
{
    auto collisionSystem = std::make_shared<CollisionSystem>();
    collisionSystem->EnableReproduction();
    Engine::GetInstance().AddSystem(collisionSystem);

    Engine::GetInstance().AddSystem(std::make_shared<CombatPowerSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<ParticleSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<CameraSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<AnimationSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<InfectionSystem>());
}

void Level3::DeleteAccessorySystems()
{
    Engine::GetInstance().DeleteSystem("CollisionSystem");
    Engine::GetInstance().DeleteSystem("CombatPowerSystem");
    Engine::GetInstance().DeleteSystem("ParticleSystem");
    Engine::GetInstance().DeleteSystem("CameraSystem");
    Engine::GetInstance().DeleteSystem("AnimationSystem");
    Engine::GetInstance().DeleteSystem("InfectionSystem");
}

void Level3::Update()
{
    LOG_D("[Level3] Updating");

    if (!Engine::GetInstance().HasEntityWithComponentOfClass("PlayerComponent"))
    {
        Engine::GetInstance().SetNextLevel(std::make_shared<LoseLevel>());
        SetFinished();
    }
    else
    {
        auto playerEntity = Engine::GetInstance().GetEntityWithComponentOfClass("PlayerComponent");
        auto reproductionComponent = std::static_pointer_cast<ReproductionComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(playerEntity, "ReproductionComponent"));

        if (reproductionComponent->GetReproduced())
        {
            Engine::GetInstance().SetNextLevel(std::make_shared<WinLevel>());
            SetFinished();
        }
    }
}

void Level3::Finish()
{
    LOG_I("[Level3] Finishing");

    Engine::GetInstance().ClearEntities();
    Engine::GetInstance().ClearSystems();
}

void Level3::MenuButtonCallback()
{
    LOG_I("[Level3] Clicked on menu button");
    SetFinished();
    Engine::GetInstance().SetNextLevel(std::make_shared<EntryLevel>());
}

void Level3::PauseButtonCallback()
{
    LOG_I("[Level3] Clicked on pause button");

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
            std::bind(&Level3::ExitButtonCallback, this));
    }
}

void Level3::ExitButtonCallback()
{
    LOG_I("[Level3] Clicked on exit button");
    SetFinished();
}