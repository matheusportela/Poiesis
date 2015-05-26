#include "poiesis/components/ParticleComponent.h"

ParticleComponent::ParticleComponent(Vector position, Vector velocity,
    Vector acceleration) :
    position(position), velocity(velocity), acceleration(acceleration)
{
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
