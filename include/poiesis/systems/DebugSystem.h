// Process entities with renderable components and render sprites.

#ifndef DEBUG_SYSTEM_H_
#define DEBUG_SYSTEM_H_

#include <string>
#include <vector>

#include "bandit/Engine.h"

#include "poiesis/components/GrowthComponent.h"
#include "poiesis/components/ParticleComponent.h"

class DebugSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
    void GenerateTimeMessage();
    void GenerateFPSMessage(float dt);
    void GenerateEngineMessage();
    void GeneratePlayerMessage();

  private:
    float currentTime;
    float accumulatedTime;
    std::vector<std::string> messages;
};

#endif // DEBUG_SYSTEM_H_