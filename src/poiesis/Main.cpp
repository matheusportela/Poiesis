#include <iostream>
#include <memory.h>

#include "bandit/Engine.h"

#include "poiesis/systems/RenderingSystem.h"
#include "poiesis/levels/Level1.h"

int main()
{
    LOG_SET_INFO();
    BANDIT_ENGINE_INIT();
    CFG_INIT("Configurations.cfg");

    Engine::GetInstance().CreateWindow(CFG_GETS("WINDOW_TITLE"),
        CFG_GETI("WINDOW_WIDTH"), CFG_GETI("WINDOW_HEIGHT"));

    // Necessary to display the window.
    Engine::GetInstance().AddSystem(std::make_shared<RenderingSystem>());

    Engine::GetInstance().SetCurrentLevel(std::make_shared<Level1>());
    Engine::GetInstance().Run();

    BANDIT_ENGINE_SHUTDOWN();
    
    return 0;
}