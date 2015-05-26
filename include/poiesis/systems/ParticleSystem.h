// Simulates particle physics.

#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/components/ParticleComponent.h"

class ParticleSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
};

#endif // PARTICLE_SYSTEM_H_