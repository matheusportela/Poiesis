#include <iostream>
#include <memory.h>

#include "bandit/Engine.h"
#include "bandit/adapters/sdl/SDLGraphicsAdapter.h"
#include "bandit/adapters/sdl/SDLSystemAdapter.h"
#include "bandit/adapters/sdl/SDLTimerAdapter.h"

int main()
{
    Engine engine(std::make_shared<SDLSystemAdapter>(),
        std::make_shared<SDLTimerAdapter>(),
        std::make_shared<SDLGraphicsAdapter>());

    engine.Run();
    
    return 0;
}