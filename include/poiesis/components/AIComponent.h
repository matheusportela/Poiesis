// Stores data relevant for artificial intelligence.

#ifndef AI_COMPONENT_H_
#define AI_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class AIComponent : public Component
{
  public:
    AIComponent(std::string pursueComponent);
    std::string GetComponentClass();
    std::string GetPursueComponent();
    void SetPursueComponent(std::string pursueComponent);

  private:
    // Holds the component type the entity pursues.
    std::string pursueComponent;
};

#endif // AI_COMPONENT_H_