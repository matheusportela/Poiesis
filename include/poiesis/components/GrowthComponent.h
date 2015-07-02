// Stores whether the entity can grow.

#ifndef GROWTH_COMPONENT_H_
#define GROWTH_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class GrowthComponent : public Component
{
  public:
    GrowthComponent(int threshold = 10);
    std::string GetComponentClass();

    int GetThreshold();
    void SetThreshold(int threshold);

    int GetLevel();
    void SetLevel(int level);

    int GetEnergy();
    void SetEnergy(int energy);

    int GetGrowthPower();
    void SetGrowthPower(int growthPower);

  private:
    // Holds the amount of power that is necessary to increase the growth level.
    int threshold;

    // Holds the current growth level.
    int level;

    // Holds the amount of energy accumulated by the entity, which indirectly
    // affects the growth power.
    int energy;

    // Holds the entity's power for growing up.
    int growthPower;
};

#endif // GROWTH_COMPONENT_H_