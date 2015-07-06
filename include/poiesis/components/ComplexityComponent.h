// Stores whether the entity can grow.

#ifndef COMPLEXITY_COMPONENT_H_
#define COMPLEXITY_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class ComplexityComponent : public Component
{
  public:
    ComplexityComponent(int maxComplexity);
    std::string GetComponentClass();

    int GetComplexity();
    void SetComplexity(int complexity);

    int GetMaxComplexity();
    void SetMaxComplexity(int maxComplexity);

  private:
    // Holds current entity complexity.
    int complexity;

    // Holds the entity's maximum complexity.
    int maxComplexity;
};

#endif // COMPLEXITY_COMPONENT_H_