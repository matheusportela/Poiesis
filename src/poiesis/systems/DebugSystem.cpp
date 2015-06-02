#include "poiesis/systems/DebugSystem.h"

std::string DebugSystem::GetName()
{
    return "DebugSystem";
}

void DebugSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[DebugSystem] Update: " << dt);

    accumulatedTime += dt;

    if (!Engine::GetInstance().GetGraphicsAdapter()->IsFontLoaded(CFG_GETP("FONT_FILE")))
        Engine::GetInstance().GetGraphicsAdapter()->LoadFont(CFG_GETP("FONT_FILE"), CFG_GETI("DEBUG_MESSAGE_SIZE"));

    if (accumulatedTime > CFG_GETF("DEBUG_MESSAGE_PERIOD"))
    {
        accumulatedTime = 0;
        fpsMessage = GenerateFPSMessage(dt);
    }

    Engine::GetInstance().GetGraphicsAdapter()->Write(fpsMessage, CFG_GETP("FONT_FILE"), CFG_GETI("DEBUG_MESSAGE_X"), CFG_GETI("DEBUG_MESSAGE_Y"));
}

std::string DebugSystem::GenerateFPSMessage(float dt)
{
    int fps = 1/dt;
    return("FPS: " + std::to_string(fps));
}