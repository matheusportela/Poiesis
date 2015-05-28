#include "poiesis/systems/ParticleSystem.h"

std::string ParticleSystem::GetName()
{
    return "ParticleSystem";
}

void ParticleSystem::Update(float dt)
{
    auto components = Engine::GetInstance().GetEntityManager()->GetAllComponentsOfClass("ParticleComponent");
    std::shared_ptr<ParticleComponent> particleComponent;

    for (auto component : components)
    {
        particleComponent = std::static_pointer_cast<ParticleComponent>(component);
        UpdateParticleProperties(particleComponent, dt);

        // Erases the force vector since if no force is applied, no acceleration
        // exists.
        particleComponent->SetForce(Vector(0, 0));
    }
}

void ParticleSystem::UpdateParticleProperties(
    std::shared_ptr<ParticleComponent> particleComponent, float dt)
{
    float inverseMass = particleComponent->GetInverseMass();
    float damping = particleComponent->GetDamping();
    Vector force = particleComponent->GetForce();
    Vector position = particleComponent->GetPosition();
    Vector velocity = particleComponent->GetVelocity();
    Vector acceleration = particleComponent->GetAcceleration();
    Vector randomVector = GenerateRandomForce();

    force += randomVector;
    position = position + velocity*dt + acceleration*dt*dt*0.5;
    velocity = velocity*damping + acceleration*dt;
    acceleration = force*inverseMass;

    particleComponent->SetPosition(position);
    particleComponent->SetVelocity(velocity);
    particleComponent->SetAcceleration(acceleration);
    particleComponent->SetForce(force);
}

Vector ParticleSystem::GenerateRandomForce()
{
    Random random;
    float randomFactor = CFG_GETF("PARTICLE_RANDOM_FORCE_MAG");
    float randomX = random.GenerateFloat(-1, 1);
    float randomY = random.GenerateFloat(-1, 1);
    Vector randomVector = Vector(randomX, randomY)*randomFactor;
    return randomVector;
}