// Stores whether the entity can be eaten.

#ifndef SLOWER_COMPONENT_H_
#define SLOWER_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class SlowerComponent : public Component
{
  public:
    SlowerComponent(float magnitude);
    std::string GetComponentClass();
    float GetMagnitude();
    void SetMagnitude(float magnitude);

  private:
    // Holds the magnitude of the slowing effect that must be applied to
    // entities. For instance, a magnitude of 0.1 reduces the entity speed in
    // 10%.
    float magnitude;
};

#endif // SLOWER_COMPONENT_H_