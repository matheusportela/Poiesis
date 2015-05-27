#include "poiesis/systems/ParticleSystem.h"

std::string ParticleSystem::GetName()
{
    return "ParticleSystem";
}

void ParticleSystem::Update(float dt)
{
    auto components = Engine::GetInstance().GetEntityManager()->GetAllComponentsOfClass("ParticleComponent");
    std::shared_ptr<ParticleComponent> particleComponent;
    float inverseMass;
    float damping;
    Vector force;
    Vector position;
    Vector velocity;
    Vector acceleration;

    for (auto component : components)
    {
        particleComponent = std::static_pointer_cast<ParticleComponent>(component);

        inverseMass = particleComponent->GetInverseMass();
        damping = particleComponent->GetDamping();
        force = particleComponent->GetForce();
        position = particleComponent->GetPosition();
        velocity = particleComponent->GetVelocity();
        acceleration = particleComponent->GetAcceleration();

        // Updating particle with kinects equations.
        position = position + velocity*dt + acceleration*dt*dt*0.5;
        velocity = velocity*damping + acceleration*dt;
        acceleration = force*inverseMass;

        // Erases the force vector since if no force is applied, no acceleration
        // exists.
        force = Vector(0, 0);

        particleComponent->SetPosition(position);
        particleComponent->SetVelocity(velocity);
        particleComponent->SetAcceleration(acceleration);
        particleComponent->SetForce(force);

        LOG_D("[ParticleSystem] Particle position: " << particleComponent->GetPosition());
        LOG_D("[ParticleSystem] Particle velocity: " << particleComponent->GetVelocity());
        LOG_D("[ParticleSystem] Particle acceleration: " << particleComponent->GetAcceleration());
        LOG_D("[ParticleSystem] Particle force: " << particleComponent->GetForce());
    }
}
