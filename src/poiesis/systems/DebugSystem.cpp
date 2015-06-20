#include "poiesis/systems/DebugSystem.h"

std::string DebugSystem::GetName()
{
    return "DebugSystem";
}

void DebugSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[DebugSystem] Update: " << dt);

    currentTime += dt;
    accumulatedTime += dt;

    if (!Engine::GetInstance().GetGraphicsAdapter()->IsFontLoaded(CFG_GETP("FONT_FILE")))
        Engine::GetInstance().GetGraphicsAdapter()->LoadFont(CFG_GETP("FONT_FILE"), CFG_GETI("DEBUG_MESSAGE_SIZE"));

    if (accumulatedTime > CFG_GETF("DEBUG_MESSAGE_PERIOD"))
    {
        accumulatedTime = 0;
        messages.clear();
        GenerateTimeMessage();
        GenerateFPSMessage(dt);
        GenerateEngineMessage();
        GeneratePlayerMessage();
    }

    for (unsigned int i = 0; i < messages.size(); ++i)
        Engine::GetInstance().GetGraphicsAdapter()->Write(messages[i],
            CFG_GETP("FONT_FILE"), CFG_GETI("DEBUG_MESSAGE_X"),
            CFG_GETI("DEBUG_MESSAGE_Y") + i*CFG_GETI("DEBUG_MESSAGE_SIZE"));
}

void DebugSystem::GenerateTimeMessage()
{
    int displayTime = currentTime;
    messages.push_back("Time: " + std::to_string(displayTime) + " s");
}

void DebugSystem::GenerateFPSMessage(float dt)
{
    int fps = 1/dt;
    messages.push_back("FPS: " + std::to_string(fps));
}

void DebugSystem::GenerateEngineMessage()
{
    messages.push_back("Engine");
    messages.push_back("Entities: " + std::to_string(Engine::GetInstance().GetEntityManager()->GetNumberOfEntities()));
}

void DebugSystem::GeneratePlayerMessage()
{
    auto followEntities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("CameraFollowComponent");

    if (followEntities.size() == 0)
        return;

    auto particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(followEntities[0], "ParticleComponent"));
    auto growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(followEntities[0], "GrowthComponent"));
    messages.push_back("Player");
    messages.push_back("Position: " + particleComponent->GetPosition().ToString());
    messages.push_back("Velocity: " + std::to_string(particleComponent->GetVelocity().GetMagnitude()) + " " + std::to_string(particleComponent->GetVelocity().GetDirection()*180.0/M_PI));
    messages.push_back("Growth: " + std::to_string(growthComponent->GetLevel()));
    messages.push_back("Energy: " + std::to_string(growthComponent->GetEnergy()));
}