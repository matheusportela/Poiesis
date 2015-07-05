// Stores data relevant for areas that enhance cell growth.

#ifndef VITAMIN_COMPONENT_H_
#define VITAMIN_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class VitaminComponent : public Component
{
  public:
    VitaminComponent(float growthFactor);
    std::string GetComponentClass();

    float GetGrowthFactor();
    void SetGrowthFactor(float growthFactor);

  private:
    // Holds the factor by which the entity growth will be enhanced.
    float growthFactor;
};

#endif // VITAMIN_COMPONENT_H_