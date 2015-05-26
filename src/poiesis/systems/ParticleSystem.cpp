#include "poiesis/systems/ParticleSystem.h"

std::string ParticleSystem::GetName()
{
    return "ParticleSystem";
}

void ParticleSystem::Update(float dt)
{
    auto components = Engine::GetInstance().GetEntityManager()->GetAllComponentsOfClass("ParticleComponent");
    std::shared_ptr<ParticleComponent> particleComponent;
    Vector position;
    Vector velocity;
    Vector acceleration;

    for (auto component : components)
    {
        particleComponent = std::static_pointer_cast<ParticleComponent>(component);

        position = particleComponent->GetPosition();
        velocity = particleComponent->GetVelocity();
        acceleration = particleComponent->GetAcceleration();

        position = position + velocity*dt + acceleration*dt*dt*0.5;
        velocity = velocity + acceleration*dt;

        particleComponent->SetPosition(position);
        particleComponent->SetVelocity(velocity);

        LOG_D("[ParticleSystem] Particle position: " << particleComponent->GetPosition());
        LOG_D("[ParticleSystem] Particle velocity: " << particleComponent->GetVelocity());
        LOG_D("[ParticleSystem] Particle acceleration: " << particleComponent->GetAcceleration());
    }
}
