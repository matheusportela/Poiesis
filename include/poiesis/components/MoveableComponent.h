// Stores whether the entity can be moved by user input.

#ifndef MOVEABLE_COMPONENT_H_
#define MOVEABLE_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class MoveableComponent : public Component
{
  public:
    MoveableComponent(bool active = true);
    std::string GetComponentClass();

    float GetActive();
    void SetActive(float active);

  private:
    float active;
};

#endif // MOVEABLE_COMPONENT_H_