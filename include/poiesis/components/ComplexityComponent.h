// Stores whether the entity can grow.

#ifndef COMPLEXITY_COMPONENT_H_
#define COMPLEXITY_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class ComplexityComponent : public Component
{
  public:
    ComplexityComponent();
    std::string GetComponentClass();

    int GetComplexity();
    void SetComplexity(int complexity);

  private:
    // Holds current entity complexity;
    int complexity;
};

#endif // COMPLEXITY_COMPONENT_H_