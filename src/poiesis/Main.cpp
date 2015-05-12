#include <memory.h>

#include "bandit/core/Engine.h"
#include "bandit/adapters/sdl/SDLTimerAdapter.h"

int main()
{
    Engine engine(std::make_shared<SDLTimerAdapter>());

    engine.Run();
    
    return 0;
}