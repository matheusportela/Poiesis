#include "poiesis/systems/DebugSystem.h"

DebugSystem::DebugSystem()
{
    timer.SetPeriod(CFG_GETF("DEBUG_MESSAGE_PERIOD"));
    timer.SetCallback(std::bind(&DebugSystem::GenerateDebugMessages, this));
}

std::string DebugSystem::GetName()
{
    return "DebugSystem";
}

void DebugSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[DebugSystem] Update: " << dt);

    currentTime += dt;
    currentFps = 1/dt;

    if (!Engine::GetInstance().GetGraphicsAdapter()->IsFontLoaded(CFG_GETP("FONT_FILE")))
        Engine::GetInstance().GetGraphicsAdapter()->LoadFont(CFG_GETP("FONT_FILE"), CFG_GETI("DEBUG_MESSAGE_SIZE"));

    timer.Update(dt);

    for (unsigned int i = 0; i < messages.size(); ++i)
        Engine::GetInstance().GetGraphicsAdapter()->Write(messages[i],
            CFG_GETP("FONT_FILE"), CFG_GETI("DEBUG_MESSAGE_X"),
            CFG_GETI("DEBUG_MESSAGE_Y") + i*CFG_GETI("DEBUG_MESSAGE_SIZE"));
}

void DebugSystem::GenerateDebugMessages()
{
    messages.clear();
    GenerateTimeMessage();
    GenerateFPSMessage();
    GenerateEngineMessage();
    GeneratePlayerMessage();
}

void DebugSystem::GenerateTimeMessage()
{
    int displayTime = currentTime;
    messages.push_back("Time: " + std::to_string(displayTime) + " s");
}

void DebugSystem::GenerateFPSMessage()
{
    messages.push_back("FPS: " + std::to_string(currentFps));
}

void DebugSystem::GenerateEngineMessage()
{
    messages.push_back("Engine");
    messages.push_back("Entities: " + std::to_string(Engine::GetInstance().GetNumberOfEntities()));
}

void DebugSystem::GeneratePlayerMessage()
{
    if (!Engine::GetInstance().HasEntityWithComponentOfClass("PlayerComponent"))
        return;

    auto playerEntity = Engine::GetInstance().GetEntityWithComponentOfClass("PlayerComponent");

    auto particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetSingleComponentOfClass(playerEntity, "ParticleComponent"));
    auto growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetSingleComponentOfClass(playerEntity, "GrowthComponent"));
    auto combatComponent = std::static_pointer_cast<CombatComponent>(Engine::GetInstance().GetSingleComponentOfClass(playerEntity, "CombatComponent"));
    auto complexityComponent = std::static_pointer_cast<ComplexityComponent>(Engine::GetInstance().GetSingleComponentOfClass(playerEntity, "ComplexityComponent"));
    messages.push_back("Player");
    messages.push_back("Position: " + particleComponent->GetPosition().ToString());
    messages.push_back("Velocity: " + std::to_string(particleComponent->GetVelocity().GetMagnitude()) + " " + std::to_string(particleComponent->GetVelocity().GetDirection()*180.0/M_PI));
    messages.push_back("Growth: " + std::to_string(growthComponent->GetLevel()));
    messages.push_back("Energy: " + std::to_string(growthComponent->GetEnergy()));
    messages.push_back("Growth power: " + std::to_string(growthComponent->GetGrowthPower()));
    messages.push_back("Combat power: " + std::to_string(combatComponent->GetPower()));
    messages.push_back("Complexity: " + std::to_string(complexityComponent->GetComplexity()));
}