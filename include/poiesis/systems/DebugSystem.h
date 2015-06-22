// Process entities with renderable components and render sprites.

#ifndef DEBUG_SYSTEM_H_
#define DEBUG_SYSTEM_H_

#include <string>
#include <vector>

#include "bandit/Engine.h"

#include "poiesis/components/CombatComponent.h"
#include "poiesis/components/GrowthComponent.h"
#include "poiesis/components/ParticleComponent.h"

class DebugSystem : public System
{
  public:
    DebugSystem();
    std::string GetName();
    void Update(float dt);
    void GenerateDebugMessages();
    void GenerateTimeMessage();
    void GenerateFPSMessage();
    void GenerateEngineMessage();
    void GeneratePlayerMessage();

  private:
    PeriodicTimer timer;
    float currentTime;
    float currentFps;
    std::vector<std::string> messages;
};

#endif // DEBUG_SYSTEM_H_