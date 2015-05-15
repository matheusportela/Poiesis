#include "bandit/Engine.h"

Engine::Engine(
    std::shared_ptr<SystemAdapter> systemAdapter,
    std::shared_ptr<TimerAdapter> timerAdapter,
    std::shared_ptr<GraphicsAdapter> graphicsAdapter) :
    systemAdapter(systemAdapter), timerAdapter(timerAdapter),
    graphicsAdapter(graphicsAdapter)
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
    graphicsAdapter->CreateWindow("Poiesis", 1920, 1080);
    graphicsAdapter->LoadImage("resources/img/ocean.jpg");

    while (true)
    {
        graphicsAdapter->RenderImage();
        timerAdapter->Sleep(1);
        LOG_D("Elapsed time: " << timerAdapter->GetElapsedTime());
    }
}