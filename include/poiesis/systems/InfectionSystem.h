// Updates entities infection status.

#ifndef INFECTION_SYSTEM_H_
#define INFECTION_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/components/InfectionComponent.h"
#include "poiesis/components/ParticleComponent.h"

class InfectionSystem : public System
{
  public:
    void SetLevel3(bool isLevel3);
    std::string GetName();
    void Update(float dt);

  private:
    bool isLevel3;
};

#endif // INFECTION_SYSTEM_H_