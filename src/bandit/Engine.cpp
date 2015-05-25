#include "bandit/Engine.h"

Engine& Engine::GetInstance()
{
    static Engine instance;
    return instance;
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
    LOG_D("Initializing engine");
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
    LOG_D("Shutting engine down");
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

    // Necessary to display the window.
    std::shared_ptr<System> renderingSystem = std::make_shared<RenderingSystem>(
        entityManager, graphicsAdapter, inputAdapter);
    AddSystem(renderingSystem);
}

void Engine::SetCurrentLevel(std::shared_ptr<Level> level)
{
    levelManager->SetCurrentLevel(level);
}

std::shared_ptr<Entity> Engine::CreateEntity()
{
    return entityManager->CreateEntity();
}

void Engine::AddComponent(std::shared_ptr<Component> component,
    std::shared_ptr<Entity> entity)
{
    entityManager->AddComponent(component, entity);
}

void Engine::AddSystem(std::shared_ptr<System> system)
{
    systemManager->AddSystem(system);
}

void Engine::Run()
{
    float dt;

    while (true)
    {
        dt = timerAdapter->GetElapsedTime();
        LOG_D("Elapsed time: " << dt);

        inputAdapter->ProcessInputs();
        if (inputAdapter->CheckInputOccurred(InputType::QuitButtonPress))
        {
            LOG_I("Quit requested");
            break;
        }

        systemManager->Update(dt);
        levelManager->Update();

        timerAdapter->Sleep(0.033);
    }
}