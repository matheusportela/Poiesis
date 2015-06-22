// Calculates the combat power for the entity in the frame.

#ifndef COMBAT_POWER_SYSTEM_H_
#define COMBAT_POWER_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/components/CombatComponent.h"
#include "poiesis/components/GrowthComponent.h"

class CombatPowerSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
};

#endif // COMBAT_POWER_SYSTEM_H_