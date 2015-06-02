// Process entities with renderable components and render sprites.

#ifndef DEBUG_SYSTEM_H_
#define DEBUG_SYSTEM_H_

#include <string>

#include "bandit/Engine.h"

class DebugSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
    std::string GenerateFPSMessage(float dt);

  private:
    float accumulatedTime;
    std::string fpsMessage;
};

#endif // DEBUG_SYSTEM_H_