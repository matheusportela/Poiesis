#include "bandit/core/Engine.h"

Engine::Engine(
    std::shared_ptr<SystemAdapter> systemAdapter,
    std::shared_ptr<TimerAdapter> timerAdapter,
    std::shared_ptr<WindowAdapter> windowAdapter) :
    systemAdapter(systemAdapter), timerAdapter(timerAdapter),
    windowAdapter(windowAdapter)
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
    windowAdapter->CreateWindow();

    while (true)
    {
        timerAdapter->Sleep(1);
        std::cout << "Elapsed time: " << timerAdapter->GetElapsedTime()
            << std::endl;
    }
}