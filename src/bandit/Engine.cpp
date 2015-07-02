#include "bandit/Engine.h"

Engine& Engine::GetInstance()
{
    static Engine instance;
    return instance;
}

std::shared_ptr<GraphicsAdapter> Engine::GetGraphicsAdapter()
{
    return graphicsAdapter;
}

std::shared_ptr<InputAdapter> Engine::GetInputAdapter()
{
    return inputAdapter;
}

std::shared_ptr<EntityManager> Engine::GetEntityManager()
{
    return entityManager;
}

std::shared_ptr<SystemManager> Engine::GetSystemManager()
{
    return systemManager;
}

std::shared_ptr<LevelManager> Engine::GetLevelManager()
{
    return levelManager;
}

void Engine::Initialize(
    std::shared_ptr<SystemAdapter> systemAdapter,
    std::shared_ptr<TimerAdapter> timerAdapter,
    std::shared_ptr<GraphicsAdapter> graphicsAdapter,
    std::shared_ptr<AudioAdapter> musicAdapter,
    std::shared_ptr<AudioAdapter> soundEffectAdapter,
    std::shared_ptr<InputAdapter> inputAdapter,
    std::shared_ptr<EntityManager> entityManager,
    std::shared_ptr<LevelManager> levelManager,
    std::shared_ptr<SystemManager> systemManager)
{
    LOG_D("[Engine] Initializing engine");
    this->systemAdapter = systemAdapter;
    this->timerAdapter = timerAdapter;
    this->graphicsAdapter = graphicsAdapter;
    this->musicAdapter = musicAdapter;
    this->soundEffectAdapter = soundEffectAdapter;
    this->inputAdapter = inputAdapter;
    this->entityManager = entityManager;
    this->levelManager = levelManager;
    this->systemManager = systemManager;

    systemAdapter->Initialize();
}

void Engine::Shutdown()
{
    LOG_D("[Engine] Shutting engine down");
    systemAdapter->Shutdown();
}

void Engine::CreateWindow(std::string title, int height, int width)
{
    if (graphicsAdapter == nullptr)
    {
        LOG_E("[Engine] Graphics adapter must be initialized before creating "
            << "an window.");
        exit(1);
    }

    if (inputAdapter == nullptr)
    {
        LOG_E("[Engine] Input adapter must be initialized before creating an "
            << "window in order to handle quit requests.");
        exit(1);
    }

    graphicsAdapter->CreateWindow(title, height, width);
}

void Engine::SetCurrentLevel(std::shared_ptr<Level> level)
{
    levelManager->SetCurrentLevel(level);
}

void Engine::SetNextLevel(std::shared_ptr<Level> level)
{
    levelManager->SetNextLevel(level);
}

std::shared_ptr<Entity> Engine::CreateEntity()
{
    return entityManager->CreateEntity();
}

void Engine::DeleteEntity(std::shared_ptr<Entity> entity)
{
    entityManager->DeleteEntity(entity);
}

void Engine::ClearEntities()
{
    entityManager->Clear();
}

std::vector<std::shared_ptr<Entity>> Engine::GetAllEntitiesWithComponentOfClass(
        std::string componentClass)
{
    return entityManager->GetAllEntitiesWithComponentOfClass(componentClass);
}

unsigned int Engine::GetNumberOfEntities()
{
    return entityManager->GetNumberOfEntities();
}

void Engine::AddComponent(std::shared_ptr<Component> component,
    std::shared_ptr<Entity> entity)
{
    entityManager->AddComponent(component, entity);
}

std::vector<std::shared_ptr<Component>> Engine::GetComponentsOfClass(
        std::shared_ptr<Entity> entity, std::string componentClass)
{
    return entityManager->GetComponentsOfClass(entity, componentClass);
}

std::shared_ptr<Component> Engine::GetSingleComponentOfClass(
    std::shared_ptr<Entity> entity, std::string componentClass)
{
    return entityManager->GetSingleComponentOfClass(entity, componentClass);
}

std::vector<std::shared_ptr<Component>> Engine::GetAllComponentsOfClass(
        std::string componentClass)
{
    return entityManager->GetAllComponentsOfClass(componentClass);
}

bool Engine::HasComponent(std::shared_ptr<Entity> entity,
    std::string componentClass)
{
    return entityManager->HasComponent(entity, componentClass);
}

void Engine::AddSystem(std::shared_ptr<System> system)
{
    systemManager->AddSystem(system);
}

void Engine::DeleteSystem(std::string name)
{
    systemManager->DeleteSystem(name);
}

void Engine::ClearSystems()
{
    systemManager->Clear();
}

float Engine::CalculateSleepTime(float currentFrameRate)
{
    static const float DESIRED_FRAME_RATE = 30;
    static const float DECREASE_FACTOR = 5;
    static const float INCREASE_FACTOR = 0.001;
    static float sleepDuration = 1/DESIRED_FRAME_RATE;

    // AIMD control law:
    // Additive when increasing sleep duration (hence, reducing frame rate).
    // This is important to get better PC performance by returning control to
    // the CPU.
    // Multiplicative when decreasing sleep duration (hence, increasing frame
    // rate) to quickly recover from frame rate drop.
    if (currentFrameRate < DESIRED_FRAME_RATE)
        sleepDuration /= DECREASE_FACTOR;
    else if (currentFrameRate > DESIRED_FRAME_RATE)
        sleepDuration += INCREASE_FACTOR;

    return sleepDuration;
}

void Engine::Run()
{
    float dt;
    float currentFrameRate;
    float sleepDuration;

    while (true)
    {
        dt = timerAdapter->GetElapsedTime();
        currentFrameRate = 1/dt;
        
        LOG_I("[Engine] Frame rate: " << currentFrameRate);
        LOG_D("[Engine] Elapsed time: " << dt);

        inputAdapter->ProcessInputs();
        if (inputAdapter->CheckInputOccurred(InputType::QuitButtonPress))
        {
            LOG_I("[Engine] Quit requested");
            break;
        }

        systemManager->Update(dt);
        levelManager->Update();

        if (levelManager->HasFinished())
        {
            LOG_I("[Engine] Finished game");
            break;
        }

        sleepDuration = CalculateSleepTime(currentFrameRate);
        LOG_D("Sleep duration: " << sleepDuration);
        timerAdapter->Sleep(sleepDuration);
    }
}