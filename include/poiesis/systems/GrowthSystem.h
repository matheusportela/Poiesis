// Grows entities with time.

#ifndef GROWTH_SYSTEM_H_
#define GROWTH_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/components/GrowthComponent.h"
#include "poiesis/components/SpriteComponent.h"

class GrowthSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);

  private:
    float accumulatedDt;
};

#endif // GROWTH_SYSTEM_H_