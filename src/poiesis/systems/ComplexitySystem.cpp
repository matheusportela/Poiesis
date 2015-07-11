#include "poiesis/systems/ComplexitySystem.h"

std::string ComplexitySystem::GetName()
{
    return "ComplexitySystem";
}

void ComplexitySystem::Update(float dt)
{
    std::shared_ptr<GrowthComponent> growthComponent;
    std::shared_ptr<SpriteComponent> spriteComponent;
    std::shared_ptr<ColliderComponent> colliderComponent;
    auto entities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("GrowthComponent");

    timer.Update(dt);

    for (auto entity : entities)
    {
        growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "GrowthComponent"));

        ConsumeEnergy(growthComponent);
        AdjustComplexityParticleDistance(entity, growthComponent);
        KillEntityWithoutEnergy(entity, growthComponent);
    }

    if (timer.HasFired())
        timer.SetTime(CFG_GETF("GROWTH_ENERGY_CONSUMING_PERIOD"));
}

void ComplexitySystem::ConsumeEnergy(std::shared_ptr<GrowthComponent> growthComponent)
{
    Random r;
    int energy = growthComponent->GetEnergy();

    if (timer.HasFired() && (r.GenerateFloat() < CFG_GETF("GROWTH_ENERGY_CONSUMING_CHANCE")))
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
        position *= 100*(5 + energy)/10.0;

        spriteComponent->SetPosition(position);
    }
}

bool ComplexitySystem::KillEntityWithoutEnergy(std::shared_ptr<Entity> entity,
    std::shared_ptr<GrowthComponent> growthComponent)
{
    if (growthComponent->GetEnergy() <= CFG_GETI("COMPLEXITY_MINIMUM_ENERGY"))
    {
        Engine::GetInstance().DeleteEntity(entity);
        return true;
    }

    return false;
}