// Stores data relevant for combat between entities.

#ifndef COMBAT_COMPONENT_H_
#define COMBAT_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class CombatComponent : public Component
{
  public:
    CombatComponent();
    CombatComponent(float power);

    std::string GetComponentClass();

    float GetPower();
    void SetPower(float power);

  private:
    // Holds the entity's combat power.
    float power;
};

#endif // COMBAT_COMPONENT_H_