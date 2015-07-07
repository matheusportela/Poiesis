#include "poiesis/components/ParticleComponent.h"

ParticleComponent::ParticleComponent(float inverseMass, Vector position,
    Vector velocity, Vector acceleration, float damping, float angle,
    float angularVelocity) :
    inverseMass(inverseMass), position(position), velocity(velocity),
    acceleration(acceleration), damping(damping), angle(angle),
    angularVelocity(angularVelocity)
{
}

float ParticleComponent::GetInverseMass()
{
    return inverseMass;
}

std::string ParticleComponent::GetComponentClass()
{
    return "ParticleComponent";
}


Vector ParticleComponent::GetPosition()
{
    return position;
}

void ParticleComponent::SetPosition(Vector position)
{
    this->position = position;
}


Vector ParticleComponent::GetVelocity()
{
    return velocity;
}

void ParticleComponent::SetVelocity(Vector velocity)
{
    this->velocity = velocity;
}


Vector ParticleComponent::GetAcceleration()
{
    return acceleration;
}

void ParticleComponent::SetAcceleration(Vector acceleration)
{
    this->acceleration = acceleration;
}

float ParticleComponent::GetDamping()
{
    return damping;
}

void ParticleComponent::SetDamping(float damping)
{
    this->damping = damping;
}

Vector ParticleComponent::GetForce()
{
    return force;
}

void ParticleComponent::SetForce(Vector force)
{
    this->force = force;
}

float ParticleComponent::GetAngle()
{
    return angle;
}

void ParticleComponent::SetAngle(float angle)
{
    this->angle = angle;
}

float ParticleComponent::GetAngularVelocity()
{
    return angularVelocity;
}

void ParticleComponent::SetAngularVelocity(float angularVelocity)
{
    this->angularVelocity = angularVelocity;
}