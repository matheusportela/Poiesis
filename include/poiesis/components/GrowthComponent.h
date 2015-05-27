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

    int GetPower();
    void SetPower(int power);

  private:
    // Holds the amount of power that is necessary to increase the growth level.
    int threshold;

    // Holds the current growth level.
    int level;

    // Holds the amount of power accumulated since the last growth.
    int power;
};

#endif // GROWTH_COMPONENT_H_