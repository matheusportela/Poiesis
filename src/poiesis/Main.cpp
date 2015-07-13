#include <iostream>
#include <memory>

#include "bandit/Engine.h"

#include "poiesis/levels/EntryLevel.h"

int main()
{
    LOG_SET_DEBUG();
    BANDIT_ENGINE_INIT();
    CFG_INIT("Configurations.cfg");

    Engine::GetInstance().CreateWindow(CFG_GETS("WINDOW_TITLE"),
        CFG_GETI("WINDOW_WIDTH"), CFG_GETI("WINDOW_HEIGHT"));

    Engine::GetInstance().SetCurrentLevel(std::make_shared<EntryLevel>());
    Engine::GetInstance().Run();

    BANDIT_ENGINE_SHUTDOWN();

    return 0;
}