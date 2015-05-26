// Stores particle properties, such as position, velocity and acceleration.

#ifndef PARTICLE_COMPONENT_H_
#define PARTICLE_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class ParticleComponent : public Component
{
  public:
    ParticleComponent(Vector position = Vector(0, 0),
        Vector velocity = Vector(0, 0), Vector acceleration = Vector(0, 0));
    std::string GetComponentClass();

    Vector GetPosition();
    void SetPosition(Vector position);

    Vector GetVelocity();
    void SetVelocity(Vector velocity);

    Vector GetAcceleration();
    void SetAcceleration(Vector acceleration);

  private:
    Vector position;
    Vector velocity;
    Vector acceleration;
};

#endif // PARTICLE_COMPONENT_H_