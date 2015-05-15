#include <iostream>
#include <memory.h>

#include "bandit/core/Engine.h"
#include "bandit/adapters/sdl/SDLSystemAdapter.h"
#include "bandit/adapters/sdl/SDLTimerAdapter.h"
#include "bandit/adapters/sdl/SDLWindowAdapter.h"

int main()
{
    Engine engine(std::make_shared<SDLSystemAdapter>(),
        std::make_shared<SDLTimerAdapter>(),
        std::make_shared<SDLWindowAdapter>("Poiesis", 1920, 1080));

    engine.Run();
    
    return 0;
}