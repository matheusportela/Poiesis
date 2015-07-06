// Stores whether the entity can be eaten.

#ifndef EATABLE_COMPONENT_H_
#define EATABLE_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class EatableComponent : public Component
{
  public:
    EatableComponent();
    std::string GetComponentClass();
};

#endif // EATABLE_COMPONENT_H_