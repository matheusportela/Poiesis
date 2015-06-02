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
        messages.clear();
        GenerateFPSMessage(dt);
        GeneratePlayerPositionMessage();
    }

    for (unsigned int i = 0; i < messages.size(); ++i)
        Engine::GetInstance().GetGraphicsAdapter()->Write(messages[i],
            CFG_GETP("FONT_FILE"), CFG_GETI("DEBUG_MESSAGE_X"),
            CFG_GETI("DEBUG_MESSAGE_Y") + i*CFG_GETI("DEBUG_MESSAGE_SIZE"));
}

void DebugSystem::GenerateFPSMessage(float dt)
{
    int fps = 1/dt;
    messages.push_back("FPS: " + std::to_string(fps));
}

void DebugSystem::GeneratePlayerPositionMessage()
{
    auto cameraEntities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("CameraComponent");
    auto cameraComponent = std::static_pointer_cast<CameraComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(cameraEntities[0], "CameraComponent"));
    Vector position = cameraComponent->GetPosition();
    messages.push_back("Camera: " + position.ToString());
}