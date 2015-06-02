#include "poiesis/systems/DebugSystem.h"

std::string DebugSystem::GetName()
{
    return "DebugSystem";
}

void DebugSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[DebugSystem] Update: " << dt);

    if (!Engine::GetInstance().GetGraphicsAdapter()->IsFontLoaded(CFG_GETP("FONT_FILE")))
        Engine::GetInstance().GetGraphicsAdapter()->LoadFont(CFG_GETP("FONT_FILE"), 20);

    WriteFPS(dt);
}

void DebugSystem::WriteFPS(float dt)
{
    float fps = 1/dt;
    std::string message = "FPS: " + std::to_string(fps);
    Engine::GetInstance().GetGraphicsAdapter()->Write(message, CFG_GETP("FONT_FILE"), 0, 0);
}