#include "poiesis/levels/Level2.h"

void Level2::Start()
{
    LOG_I("[Level2] Starting");
    
    CreateAllEntities();
    CreateAllSystems();
}

void Level2::CreateAllEntities()
{
    EntityFactory::CreateBackground();
    EntityFactory::CreateCamera(CFG_GETF("LEVEL_2_CAMERA_HEIGHT"));

    CreateButtons();

    // Cells and food must be created after areas to be rendered above them.
    EntityFactory::CreatePlayer();

    CreateCells();
}

void Level2::CreateButtons()
{
    EntityFactory::CreateButton(CFG_GETP("MENU_BUTTON_IMAGE"),
        Rectangle(CFG_GETF("LEVEL_2_MENU_BUTTON_X"),
            CFG_GETF("LEVEL_2_MENU_BUTTON_Y"),
            CFG_GETF("LEVEL_2_MENU_BUTTON_WIDTH"),
            CFG_GETF("LEVEL_2_MENU_BUTTON_HEIGHT")),
        std::bind(&Level2::MenuButtonCallback, this));

    EntityFactory::CreateButton(CFG_GETP("PAUSE_BUTTON_IMAGE"),
        Rectangle(CFG_GETF("LEVEL_2_PAUSE_BUTTON_X"),
            CFG_GETF("LEVEL_2_PAUSE_BUTTON_Y"),
            CFG_GETF("LEVEL_2_PAUSE_BUTTON_WIDTH"),
            CFG_GETF("LEVEL_2_PAUSE_BUTTON_HEIGHT")),
        std::bind(&Level2::PauseButtonCallback, this));
}

void Level2::CreateCells()
{
    Random r;
    float x;
    float y;

    for (int i = 0; i < CFG_GETI("LEVEL_2_INITIAL_NUM_CELLS"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_X"), CFG_GETF("LEVEL_2_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_Y"), CFG_GETF("LEVEL_2_MAX_Y"));
        EntityFactory::CreateRandomCell(Vector(x, y));
    }
}

void Level2::CreateAllSystems()
{
    CreateEssentialSystems();
    CreateAccessorySystems();
}

void Level2::CreateEssentialSystems()
{
    Engine::GetInstance().AddSystem(std::make_shared<RenderingSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<InputSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<DebugSystem>());
}

void Level2::CreateAccessorySystems()
{
    Engine::GetInstance().AddSystem(std::make_shared<CombatPowerSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<CollisionSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<ParticleSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<CameraSystem>());
}

void Level2::DeleteAccessorySystems()
{
    Engine::GetInstance().DeleteSystem("CellSpawningSystem");
    Engine::GetInstance().DeleteSystem("CombatPowerSystem");
    Engine::GetInstance().DeleteSystem("CollisionSystem");
    Engine::GetInstance().DeleteSystem("ParticleSystem");
    Engine::GetInstance().DeleteSystem("CameraSystem");
}

void Level2::Update()
{
    LOG_D("[Level2] Updating");
}

void Level2::Finish()
{
    LOG_I("[Level2] Finishing");

    Engine::GetInstance().ClearEntities();
    Engine::GetInstance().ClearSystems();
}

void Level2::MenuButtonCallback()
{
    LOG_I("[Level2] Clicked on menu button");
    SetFinished();
    Engine::GetInstance().SetNextLevel(std::make_shared<EntryLevel>());
}

void Level2::PauseButtonCallback()
{
    LOG_I("[Level2] Clicked on pause button");

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
            Rectangle(CFG_GETF("LEVEL_2_PAUSE_MENU_EXIT_BUTTON_X"),
                CFG_GETF("LEVEL_2_PAUSE_MENU_EXIT_BUTTON_Y"),
                CFG_GETF("LEVEL_2_PAUSE_MENU_EXIT_BUTTON_WIDTH"),
                CFG_GETF("LEVEL_2_PAUSE_MENU_EXIT_BUTTON_HEIGHT")),
            std::bind(&Level2::ExitButtonCallback, this));
    }
}

void Level2::ExitButtonCallback()
{
    LOG_I("[Level2] Clicked on exit button");
    SetFinished();
}