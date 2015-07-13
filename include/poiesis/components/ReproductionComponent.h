#ifndef REPRODUCTION_COMPONENT_H_
#define REPRODUCTION_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class ReproductionComponent : public Component
{
  public:
    ReproductionComponent(int type);
    std::string GetComponentClass();

    int GetType();
    void SetType(int type);

    bool GetReproduced();
    void SetReproduced(bool reproduced);

    bool GetEnabled();
    void SetEnabled(bool enabled);

  private:
    // Holds whether can reproduce.
    bool enabled;

    // Holds whether the entity has reproduced.
    bool reproduced;

    // Holds the type of the reproduction system, which allows an entity to
    // reproduce.
    int type;
};

#endif // REPRODUCTION_COMPONENT_H_