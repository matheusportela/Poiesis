// Stores particle properties, such as position, velocity and acceleration.

#ifndef PARTICLE_COMPONENT_H_
#define PARTICLE_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class ParticleComponent : public Component
{
  public:
    ParticleComponent(float inverseMass = 0, Vector position = Vector(0, 0),
        Vector velocity = Vector(0, 0), Vector acceleration = Vector(0, 0),
        float damping = 1);
    std::string GetComponentClass();

    float GetInverseMass();

    Vector GetPosition();
    void SetPosition(Vector position);

    Vector GetVelocity();
    void SetVelocity(Vector velocity);

    Vector GetAcceleration();
    void SetAcceleration(Vector acceleration);

    float GetDamping();
    void SetDamping(float damping);

    Vector GetForce();
    void SetForce(Vector force);

  private:
    // Holds the inverse mass of a particle, which provides inertial
    // properties. Inverse mass is preferred since immovable particles have 0
    // inverse mass (or infinite mass). Also, acceleration can be calculated
    // by multiplying the inverse mass with the applied force.
    float inverseMass;

    // Holds the linear position of a particle in the world.
    Vector position;

    // Holds the linear velocity of a particle in the world.
    Vector velocity;

    // Holds the acceleration of a particle, such as the gravity acceleration.
    Vector acceleration;

    // Holds the damping factor to simulate velocity decay.
    float damping;

    // Holds the force applied to the particle in the current instant.
    Vector force;
};

#endif // PARTICLE_COMPONENT_H_