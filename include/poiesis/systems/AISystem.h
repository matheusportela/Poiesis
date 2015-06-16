// Creates food with time.

#ifndef AI_SYSTEM_H_
#define AI_SYSTEM_H_

#include <limits>

#include "bandit/Engine.h"

#include "poiesis/components/AIComponent.h"
#include "poiesis/components/EatableComponent.h"
#include "poiesis/components/ParticleComponent.h"

class AISystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);

  private:
    float accumulatedTime;
};

#endif // AI_SYSTEM_H_