#include "poiesis/levels/Level2.h"

void Level2::Start()
{
    LOG_I("[Level2] Starting");

    finished = false;
    CreateAllEntities();
    CreateAllSystems();
}

void Level2::CreateAllEntities()
{
    // EntityFactory::CreateBackground();
    EntityFactory::CreateCamera(CFG_GETF("LEVEL_2_CAMERA_HEIGHT"));

    // if (!Engine::GetInstance().HasEntityWithComponentOfClass("CameraComponent"))
    //     EntityFactory::CreateCamera(CFG_GETF("LEVEL_2_CAMERA_HEIGHT"));

    CreateButtons();
    CreateAreas();

    auto player = EntityFactory::CreatePlayer(); 
    Engine::GetInstance().AddComponent(
        std::make_shared<AIComponent>("CellParticleComponent"), player);

    // Cells and food must be created after areas to be rendered above them.
    // if (Engine::GetInstance().HasEntityWithComponentOfClass("PlayerComponent"))
    // {
    //     auto player = Engine::GetInstance().GetEntityWithComponentOfClass("PlayerComponent");
    //     Engine::GetInstance().DeleteComponentsOfClass(player, "AIComponent");
    //     Engine::GetInstance().AddComponent(
    //         std::make_shared<AIComponent>("CellParticleComponent"), player);
    // }
    // else
    // {
    //    auto player = EntityFactory::CreatePlayer(); 
    //    Engine::GetInstance().AddComponent(
    //         std::make_shared<AIComponent>("CellParticleComponent"), player);
    // }

    CreateCells();
    CreateBacteria();
    CreateViruses();
    CreateFood();
    CreateCellParticles();
}

void Level2::CreateButtons()
{
    // EntityFactory::CreateButton(CFG_GETP("MENU_BUTTON_IMAGE"),
    //     Rectangle(CFG_GETF("LEVEL_COMMON_MENU_BUTTON_X"),
    //         CFG_GETF("LEVEL_COMMON_MENU_BUTTON_Y"),
    //         CFG_GETF("LEVEL_COMMON_MENU_BUTTON_WIDTH"),
    //         CFG_GETF("LEVEL_COMMON_MENU_BUTTON_HEIGHT")),
    //     std::bind(&Level2::MenuButtonCallback, this));

    EntityFactory::CreateButton(CFG_GETP("PAUSE_BUTTON_IMAGE"),
        Rectangle(CFG_GETF("LEVEL_COMMON_PAUSE_BUTTON_X"),
            CFG_GETF("LEVEL_COMMON_PAUSE_BUTTON_Y"),
            CFG_GETF("LEVEL_COMMON_PAUSE_BUTTON_WIDTH"),
            CFG_GETF("LEVEL_COMMON_PAUSE_BUTTON_HEIGHT")),
        std::bind(&Level2::PauseButtonCallback, this));
}

void Level2::CreateAreas()
{
    Random r;
    float x;
    float y;

    for (int i = 0; i < CFG_GETI("LEVEL_2_NUM_SLOW_AREAS"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_X"), CFG_GETF("LEVEL_2_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_Y"), CFG_GETF("LEVEL_2_MAX_Y"));
        EntityFactory::CreateSlowArea(Vector(x, y));
    }

    for (int i = 0; i < CFG_GETI("LEVEL_2_NUM_FAST_AREAS"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_X"), CFG_GETF("LEVEL_2_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_Y"), CFG_GETF("LEVEL_2_MAX_Y"));
        EntityFactory::CreateFastArea(Vector(x, y));
    }

    for (int i = 0; i < CFG_GETI("LEVEL_2_NUM_VITAMIN_AREAS"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_X"), CFG_GETF("LEVEL_2_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_Y"), CFG_GETF("LEVEL_2_MAX_Y"));
        EntityFactory::CreateVitaminArea(Vector(x, y));
    }

    for (int i = 0; i < CFG_GETI("LEVEL_2_NUM_ACID_AREAS"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_X"), CFG_GETF("LEVEL_2_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_Y"), CFG_GETF("LEVEL_2_MAX_Y"));
        EntityFactory::CreateAcidArea(Vector(x, y));
    }
}

void Level2::CreateCells()
{
    Random r;
    float x;
    float y;
    std::shared_ptr<Entity> cell;

    for (int i = 0; i < CFG_GETI("LEVEL_2_INITIAL_NUM_CELLS"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_X"), CFG_GETF("LEVEL_2_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_Y"), CFG_GETF("LEVEL_2_MAX_Y"));
        cell = EntityFactory::CreateCell(Vector(x, y));
        Engine::GetInstance().AddComponent(
            std::make_shared<AIComponent>("CellParticleComponent"), cell);
    }
}

void Level2::CreateBacteria()
{
    Random r;
    float x;
    float y;

    for (int i = 0; i < CFG_GETI("LEVEL_2_INITIAL_NUM_BACTERIA"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_X"), CFG_GETF("LEVEL_2_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_Y"), CFG_GETF("LEVEL_2_MAX_Y"));
        EntityFactory::CreateBacterium(Vector(x, y));
    }
}

void Level2::CreateViruses()
{
    Random r;
    float x;
    float y;

    for (int i = 0; i < CFG_GETI("LEVEL_2_INITIAL_NUM_VIRUSES"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_X"), CFG_GETF("LEVEL_2_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_Y"), CFG_GETF("LEVEL_2_MAX_Y"));
        EntityFactory::CreateVirus(Vector(x, y));
    }
}

void Level2::CreateFood()
{
    Random r;
    float x;
    float y;

    for (int i = 0; i < CFG_GETI("LEVEL_2_INITIAL_NUM_FOOD"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_X"), CFG_GETF("LEVEL_2_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_Y"), CFG_GETF("LEVEL_2_MAX_Y"));
        EntityFactory::CreateFood(Vector(x, y));
    }
}

void Level2::CreateCellParticles()
{
    Random r;
    float x;
    float y;

    for (int i = 0; i < CFG_GETI("LEVEL_2_INITIAL_NUM_CELL_PARTICLES"); ++i)
    {
        x = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_X"), CFG_GETF("LEVEL_2_MAX_X"));
        y = r.GenerateFloat(CFG_GETF("LEVEL_2_MIN_Y"), CFG_GETF("LEVEL_2_MAX_Y"));
        EntityFactory::CreateCellParticle(Vector(x, y));
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
    
    if (CFG_GETB("DEBUG"))
        Engine::GetInstance().AddSystem(std::make_shared<DebugSystem>());
}

void Level2::CreateAccessorySystems()
{
    // Engine::GetInstance().AddSystem(std::make_shared<SpawningSystem>(
    //     CellParticleSpawning,
    //     CFG_GETF("CELL_PARTICLE_SPAWNING_CHANCE"),
    //     CFG_GETF("CELL_PARTICLE_SPAWNING_PERIOD")));
    Engine::GetInstance().AddSystem(std::make_shared<SpawningSystem>(
        FoodSpawning,
        CFG_GETF("FOOD_SPAWNING_CHANCE"),
        CFG_GETF("FOOD_SPAWNING_PERIOD")));
    Engine::GetInstance().AddSystem(std::make_shared<CombatPowerSystem>());

    auto collisionSystem = std::make_shared<CollisionSystem>();
    collisionSystem->EnableComplexity();
    Engine::GetInstance().AddSystem(collisionSystem);

    Engine::GetInstance().AddSystem(std::make_shared<ParticleSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<CameraSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<ComplexitySystem>());
    Engine::GetInstance().AddSystem(std::make_shared<AISystem>());
    Engine::GetInstance().AddSystem(std::make_shared<AnimationSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<InfectionSystem>());
}

void Level2::DeleteAccessorySystems()
{
    Engine::GetInstance().DeleteSystem("SpawningSystem");
    Engine::GetInstance().DeleteSystem("CombatPowerSystem");
    Engine::GetInstance().DeleteSystem("CollisionSystem");
    Engine::GetInstance().DeleteSystem("ParticleSystem");
    Engine::GetInstance().DeleteSystem("ComplexitySystem");
    Engine::GetInstance().DeleteSystem("AISystem");
    Engine::GetInstance().DeleteSystem("CameraSystem");
    Engine::GetInstance().DeleteSystem("AnimationSystem");
    Engine::GetInstance().DeleteSystem("InfectionSystem");
}

void Level2::Update()
{
    LOG_D("[Level2] Updating");

    if (finished)
    {
        ZoomOutEffect();
    }
    else
    {
        if (!Engine::GetInstance().HasEntityWithComponentOfClass("PlayerComponent"))
        {
            Engine::GetInstance().SetNextLevel(std::make_shared<LoseLevel>());
            SetFinished();
        }
        else
        {
            auto playerEntity = Engine::GetInstance().GetEntityWithComponentOfClass("PlayerComponent");
            auto complexityComponent = std::static_pointer_cast<ComplexityComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(playerEntity, "ComplexityComponent"));

            if (complexityComponent->GetComplexity() == CFG_GETI("LEVEL_2_GOAL_COMPLEXITY"))
            {
                finished = true;
                Engine::GetInstance().DeleteSystem("CollisionSystem");

                auto spriteComponents = Engine::GetInstance().GetComponentsOfClass(playerEntity, "SpriteComponent");
                Engine::GetInstance().GetEntityManager()->DeleteComponentsOfClass(playerEntity, "SpriteComponent");
                auto sprite = std::static_pointer_cast<SpriteComponent>(spriteComponents[0]);
                auto animation = std::make_shared<SpriteComponent>(
                    CFG_GETP("CELL_TO_REPRODUCTION_ANIMATION"),
                    Vector(0, 0), sprite->GetRotation(),
                    sprite->GetRotationSpeed(), true,
                    CFG_GETF("CELL_TO_REPRODUCTION_SCALE"),
                    CFG_GETI("CELL_TO_REPRODUCTION_NUM_FRAMES"),
                    CFG_GETF("CELL_TO_REPRODUCTION_FRAME_DURATION"), false, true);
                animation->SetCurrentFrame(0);
                Engine::GetInstance().AddComponent(animation, playerEntity);
            }
        }
    }
}

void Level2::Finish()
{
    LOG_I("[Level2] Finishing");

    Engine::GetInstance().ClearEntities();
    Engine::GetInstance().ClearSystems();
}

void Level2::ZoomOutEffect()
{
    auto cameraEntity = Engine::GetInstance().GetEntityWithComponentOfClass("CameraComponent");
    auto cameraComponent = std::static_pointer_cast<CameraComponent>(Engine::GetInstance().GetSingleComponentOfClass(cameraEntity, "CameraComponent"));
    auto height = cameraComponent->GetHeight();

    if (height < CFG_GETF("LEVEL_3_CAMERA_HEIGHT"))
    {
        height += 0.01;
        cameraComponent->SetHeight(height);
    }
    else
    {
        Engine::GetInstance().SetNextLevel(std::make_shared<Level3>());
        SetFinished();
    }
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
        // Engine::GetInstance().DeleteEntity(pauseMenuExitButton);
        Engine::GetInstance().DeleteEntity(pauseMenuButton);
    }
    else
    {
        paused = true;
        DeleteAccessorySystems();
        // pauseMenuExitButton = EntityFactory::CreateButton(
        //     CFG_GETP("EXIT_BUTTON_IMAGE"),
        //     Rectangle(CFG_GETF("LEVEL_COMMON_PAUSE_MENU_EXIT_BUTTON_X"),
        //         CFG_GETF("LEVEL_COMMON_PAUSE_MENU_EXIT_BUTTON_Y"),
        //         CFG_GETF("LEVEL_COMMON_PAUSE_MENU_EXIT_BUTTON_WIDTH"),
        //         CFG_GETF("LEVEL_COMMON_PAUSE_MENU_EXIT_BUTTON_HEIGHT")),
        //     std::bind(&Level2::ExitButtonCallback, this));

        pauseMenuButton = EntityFactory::CreateButton(CFG_GETP("MENU_BUTTON_IMAGE"),
            Rectangle(CFG_GETF("LEVEL_COMMON_MENU_BUTTON_X"),
                CFG_GETF("LEVEL_COMMON_MENU_BUTTON_Y"),
                CFG_GETF("LEVEL_COMMON_MENU_BUTTON_WIDTH"),
                CFG_GETF("LEVEL_COMMON_MENU_BUTTON_HEIGHT")),
            std::bind(&Level2::MenuButtonCallback, this));
    }
}

void Level2::ExitButtonCallback()
{
    LOG_I("[Level2] Clicked on exit button");
    SetFinished();
}