#include "bandit/Engine.h"

Engine& Engine::GetInstance()
{
    static Engine instance;
    return instance;
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

void Engine::Run()
{
    graphicsAdapter->CreateWindow("Poiesis", 1920, 1080);

    std::shared_ptr<System> renderingSystem = std::make_shared<RenderingSystem>(
        entityManager, graphicsAdapter, inputAdapter);
    systemManager->AddSystem(renderingSystem);

    float dt;

    while (true)
    {
        dt = timerAdapter->GetElapsedTime();
        LOG_D("Elapsed time: " << timerAdapter->GetElapsedTime());

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