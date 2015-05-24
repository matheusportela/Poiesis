#include "bandit/Engine.h"

Engine::Engine(
    std::shared_ptr<SystemAdapter> systemAdapter,
    std::shared_ptr<TimerAdapter> timerAdapter,
    std::shared_ptr<GraphicsAdapter> graphicsAdapter,
    std::shared_ptr<AudioAdapter> musicAdapter,
    std::shared_ptr<AudioAdapter> soundEffectAdapter,
    std::shared_ptr<InputAdapter> inputAdapter) :
    systemAdapter(systemAdapter), timerAdapter(timerAdapter),
    graphicsAdapter(graphicsAdapter), musicAdapter(musicAdapter),
    soundEffectAdapter(soundEffectAdapter), inputAdapter(inputAdapter)
{
    LOG_D("Initializing engine");
    systemAdapter->Initialize();
    entityManager = std::make_shared<EntityManager>();
    systemManager = std::make_shared<SystemManager>();
}

Engine::~Engine()
{
    LOG_D("Shutting engine down");
    systemAdapter->Shutdown();
}

void Engine::Run()
{
    CFG_INIT("Configurations.cfg");
    graphicsAdapter->CreateWindow("Poiesis", 1920, 1080);
    graphicsAdapter->LoadImage("resources/img/ocean.jpg");

    musicAdapter->Load("resources/music/stageState.ogg");
    musicAdapter->Play("resources/music/stageState.ogg");

    soundEffectAdapter->Load("resources/sound_effect/boom.wav");
    soundEffectAdapter->Play("resources/sound_effect/boom.wav");


    std::shared_ptr<Entity> windowEntity = entityManager->CreateEntity();
    entityManager->AddComponent(std::make_shared<SpriteComponent>("resources/img/ocean.jpg"), windowEntity);

    std::shared_ptr<Entity> playerEntity = entityManager->CreateEntity();
    entityManager->AddComponent(std::make_shared<SpriteComponent>("resources/img/penguin.png"), playerEntity);

    std::shared_ptr<System> renderingSystem
        = std::make_shared<RenderingSystem>(entityManager, graphicsAdapter,
            inputAdapter);
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

        timerAdapter->Sleep(0.033);
    }
}