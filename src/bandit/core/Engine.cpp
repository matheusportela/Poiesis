#include "bandit/core/Engine.h"

Engine::Engine(std::shared_ptr<TimerAdapter> timerAdapter) :
    timerAdapter(timerAdapter)
{
    std::cout << "Initializing engine" << std::endl;
}

Engine::~Engine()
{
    std::cout << "Destroying engine" << std::endl;
}

void Engine::Run()
{
    while (true)
    {
        timerAdapter->Sleep(1);
        std::cout << "Elapsed time: " << timerAdapter->GetElapsedTime()
            << std::endl;
    }
}