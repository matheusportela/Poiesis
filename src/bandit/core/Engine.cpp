#include "bandit/core/Engine.h"

Engine::Engine(
    std::shared_ptr<SystemAdapter> systemAdapter,
    std::shared_ptr<TimerAdapter> timerAdapter,
    std::shared_ptr<GraphicsAdapter> graphicsAdapter) :
    systemAdapter(systemAdapter), timerAdapter(timerAdapter),
    graphicsAdapter(graphicsAdapter)
{
    std::cout << "Initializing engine" << std::endl;
    systemAdapter->Initialize();
}

Engine::~Engine()
{
    std::cout << "Shutting engine down" << std::endl;
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
        std::cout << "Elapsed time: " << timerAdapter->GetElapsedTime()
            << std::endl;
    }
}