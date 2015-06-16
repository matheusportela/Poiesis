// Stores data relevant for artificial intelligence.

#ifndef AI_COMPONENT_H_
#define AI_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class AIComponent : public Component
{
  public:
    AIComponent();
    std::string GetComponentClass();

  private:
};

#endif // AI_COMPONENT_H_