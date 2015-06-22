// Stores data relevant for combat between entities.

#ifndef COMBAT_COMPONENT_H_
#define COMBAT_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class CombatComponent : public Component
{
  public:
    CombatComponent();
    CombatComponent(int power);

    std::string GetComponentClass();

    int GetPower();
    void SetPower(int power);

  private:
    // Holds the entity's combat power.
    int power;
};

#endif // COMBAT_COMPONENT_H_