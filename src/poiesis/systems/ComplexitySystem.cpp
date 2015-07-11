#include "poiesis/systems/ComplexitySystem.h"

std::string ComplexitySystem::GetName()
{
    return "ComplexitySystem";
}

void ComplexitySystem::Update(float dt)
{
    std::shared_ptr<GrowthComponent> growthComponent;
    std::shared_ptr<SpriteComponent> spriteComponent;
    std::shared_ptr<ComplexityComponent> complexityComponent;
    auto entities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("GrowthComponent");

    timer.Update(dt);

    for (auto entity : entities)
    {
        growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "GrowthComponent"));
        complexityComponent = std::static_pointer_cast<ComplexityComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "ComplexityComponent"));

        ConsumeEnergy(growthComponent);
        AdjustComplexityParticleDistance(entity, growthComponent);
        EmitParticle(entity);
        KillEntityWithoutEnergy(entity, growthComponent);
    }

    if (timer.HasFired())
        timer.SetTime(CFG_GETF("COMPLEXITY_ENERGY_CONSUMING_PERIOD"));
}

void ComplexitySystem::ConsumeEnergy(std::shared_ptr<GrowthComponent> growthComponent)
{
    Random r;
    int energy = growthComponent->GetEnergy();

    if (timer.HasFired() && (r.GenerateFloat() < CFG_GETF("COMPLEXITY_ENERGY_CONSUMING_CHANCE")))
        --energy;

    growthComponent->SetEnergy(energy);
}

void ComplexitySystem::AdjustComplexityParticleDistance(
    std::shared_ptr<Entity> entity,
    std::shared_ptr<GrowthComponent> growthComponent)
{
    auto spriteComponents = Engine::GetInstance().GetComponentsOfClass(entity, "SpriteComponent");
    std::shared_ptr<SpriteComponent> spriteComponent;

    for (unsigned int i = 1; i < spriteComponents.size(); ++i)
    {
        spriteComponent = std::static_pointer_cast<SpriteComponent>(spriteComponents[i]);
        auto position = spriteComponent->GetPosition();
        auto energy = growthComponent->GetEnergy();

        position.Normalize();
        position *= 100*(5 - energy)/10.0;

        spriteComponent->SetPosition(position);
    }
}

bool ComplexitySystem::KillEntityWithoutEnergy(std::shared_ptr<Entity> entity,
    std::shared_ptr<GrowthComponent> growthComponent)
{
    if (growthComponent->GetEnergy() > CFG_GETI("COMPLEXITY_MAXIMUM_ENERGY"))
    {
        Engine::GetInstance().DeleteEntity(entity);
        return true;
    }

    return false;
}

void ComplexitySystem::EmitParticle(std::shared_ptr<Entity> entity)
{
    auto growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "GrowthComponent"));
    auto complexityComponent = std::static_pointer_cast<ComplexityComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "ComplexityComponent"));

    if (growthComponent->GetEnergy() < CFG_GETI("COMPLEXITY_MINIMUM_ENERGY"))
    {
        auto particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "ParticleComponent"));
        auto spriteComponents = Engine::GetInstance().GetComponentsOfClass(entity, "SpriteComponent");

        if (spriteComponents.size() == 1)
            return;

        Engine::GetInstance().GetEntityManager()->DeleteComponentsOfClass(entity, "SpriteComponent");

        for (unsigned int i = 0; i < spriteComponents.size()-1; ++i)
        {
            auto spriteComponent = spriteComponents[i];
            Engine::GetInstance().AddComponent(spriteComponent, entity);
        }

        auto sprite = std::static_pointer_cast<SpriteComponent>(spriteComponents[spriteComponents.size()-1]);
        Vector cellParticlePosition = particleComponent->GetPosition() + sprite->GetPosition();
        Vector cellParticleForce = sprite->GetPosition()*1.25;
        cellParticleForce.Normalize();
        cellParticleForce.Rotate(particleComponent->GetAngle());
        cellParticleForce *= CFG_GETF("COMPLEXITY_PARTICLE_EMIT_FORCE");

        complexityComponent->SetComplexity(complexityComponent->GetComplexity() - 1);
        growthComponent->SetEnergy(0);

        auto cellParticle = EntityFactory::CreateCellParticle(cellParticlePosition);
        auto cellParticleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetSingleComponentOfClass(cellParticle, "ParticleComponent"));
        cellParticleComponent->SetForce(cellParticleForce);
        cellParticleComponent->SetVelocity(particleComponent->GetVelocity());
    }
}