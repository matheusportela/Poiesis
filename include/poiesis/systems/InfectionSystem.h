// Updates entities infection status.

#ifndef INFECTION_SYSTEM_H_
#define INFECTION_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/components/InfectionComponent.h"

class InfectionSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
};

#endif // INFECTION_SYSTEM_H_