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
    void UpdateParticleProperties(
        std::shared_ptr<ParticleComponent> particleComponent, float dt);
    Vector GenerateRandomForce();
};

#endif // PARTICLE_SYSTEM_H_