// Run basic engine initialization and shutdown methods.
//
// Some modules must be initialized in order to provide functionality to the
// higher-level modules. Also, they must be properly shutdown, avoiding memory
// leaks and system crashing.

#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <memory>

#include "bandit/adapters/GraphicsAdapter.h"
#include "bandit/adapters/SystemAdapter.h"
#include "bandit/adapters/TimerAdapter.h"

class Engine
{
  public:
    Engine(std::shared_ptr<SystemAdapter> systemAdapter,
        std::shared_ptr<TimerAdapter> timerAdapter,
        std::shared_ptr<GraphicsAdapter> graphicsAdapter);
    ~Engine();

    // Executes the engine main loop.
    void Run();

  private:
    std::shared_ptr<SystemAdapter> systemAdapter;
    std::shared_ptr<TimerAdapter> timerAdapter;
    std::shared_ptr<GraphicsAdapter> graphicsAdapter;
};

#endif // ENGINE_H_