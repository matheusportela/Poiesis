#include "bandit/Engine.h"

Engine::Engine(
    std::shared_ptr<SystemAdapter> systemAdapter,
    std::shared_ptr<TimerAdapter> timerAdapter,
    std::shared_ptr<GraphicsAdapter> graphicsAdapter,
    std::shared_ptr<AudioAdapter> musicAdapter,
    std::shared_ptr<AudioAdapter> soundEffectAdapter) :
    systemAdapter(systemAdapter), timerAdapter(timerAdapter),
    graphicsAdapter(graphicsAdapter), musicAdapter(musicAdapter),
    soundEffectAdapter(soundEffectAdapter)
{
    LOG_D("Initializing engine");
    systemAdapter->Initialize();
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
    musicAdapter->Play();

    soundEffectAdapter->Load("resources/sound_effect/boom.wav");
    soundEffectAdapter->Play();

    while (true)
    {
        graphicsAdapter->RenderImage();
        timerAdapter->Sleep(1);
        LOG_D("Elapsed time: " << timerAdapter->GetElapsedTime());
    }
}