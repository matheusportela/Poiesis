// Stores data for areas that modify cell speed.

#ifndef SLOWING_COMPONENT_H_
#define SLOWING_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class SlowingComponent : public Component
{
  public:
    SlowingComponent(float magnitude);
    std::string GetComponentClass();
    float GetMagnitude();
    void SetMagnitude(float magnitude);

  private:
    // Holds the magnitude of the slowing effect that must be applied to
    // entities. For instance, a magnitude of 0.1 reduces the entity speed in
    // 10%.
    float magnitude;
};

#endif // SLOWING_COMPONENT_H_