#include "poiesis/systems/GrowthSystem.h"

std::string GrowthSystem::GetName()
{
    return "GrowthSystem";
}

void GrowthSystem::Update(float dt)
{
    std::shared_ptr<GrowthComponent> growthComponent;
    std::shared_ptr<SpriteComponent> spriteComponent;
    std::shared_ptr<ColliderComponent> colliderComponent;
    auto entities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("GrowthComponent");

    timer.Update(dt);

    for (auto entity : entities)
    {
        // Load entity's data
        growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "GrowthComponent"));
        colliderComponent = std::static_pointer_cast<ColliderComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "ColliderComponent"));

        // Execute growth logic
        ConsumeEnergy(growthComponent);
        UpdateGrowthPower(growthComponent);
        GrowOrShrink(entity, growthComponent);
        SaturateLevel(growthComponent);

        if (KillSmallEntity(entity, growthComponent))
            continue;

        UpdateCollisionRadius(growthComponent, colliderComponent);

        // Save entity's data
        for (auto component : Engine::GetInstance().GetComponentsOfClass(entity, "SpriteComponent"))
        {
            spriteComponent = std::static_pointer_cast<SpriteComponent>(component);
            UpdateSpriteSize(spriteComponent, growthComponent);
            UpdateSpriteFrameDuration(spriteComponent, growthComponent);
        }
    }

    if (timer.HasFired())
        timer.SetTime(CFG_GETF("GROWTH_ENERGY_CONSUMING_PERIOD"));
}

void GrowthSystem::ConsumeEnergy(std::shared_ptr<GrowthComponent> growthComponent)
{
    Random r;
    int energy = growthComponent->GetEnergy();

    if (timer.HasFired() && (r.GenerateFloat() < CFG_GETF("GROWTH_ENERGY_CONSUMING_CHANCE")))
        --energy;

    growthComponent->SetEnergy(energy);
}

void GrowthSystem::UpdateGrowthPower(std::shared_ptr<GrowthComponent> growthComponent)
{
    int growthPower = growthComponent->GetGrowthPower();
    growthPower += CalculateGrowthDelta(growthComponent);
    growthComponent->SetGrowthPower(growthPower);
}

int GrowthSystem::CalculateGrowthDelta(std::shared_ptr<GrowthComponent> growthComponent)
{
    int energy = growthComponent->GetEnergy();
    int delta;

    if (energy <= CFG_GETI("GROWTH_ENERGY_LEVEL_FAST_SHRINK"))
        delta = CFG_GETI("GROWTH_DELTA_FAST_SHRINK");
    else if (energy <= CFG_GETI("GROWTH_ENERGY_LEVEL_SHRINK"))
        delta = CFG_GETI("GROWTH_DELTA_SHRINK");
    else if (energy <= CFG_GETI("GROWTH_ENERGY_LEVEL_STAGNATION"))
        delta = CFG_GETI("GROWTH_DELTA_STAGNATION");
    else if (energy <= CFG_GETI("GROWTH_ENERGY_LEVEL_GROW"))
        delta = CFG_GETI("GROWTH_DELTA_GROW");
    else
        delta = CFG_GETI("GROWTH_DELTA_FAST_GROW");

    return delta;
}

void GrowthSystem::GrowOrShrink(std::shared_ptr<Entity> entity,
    std::shared_ptr<GrowthComponent> growthComponent)
{
    int growthPower = growthComponent->GetGrowthPower();

    if (growthPower >= CFG_GETI("GROWTH_UPPER_THRESHOLD"))
        Grow(entity, growthComponent);
    else if (growthPower <= CFG_GETI("GROWTH_LOWER_THRESHOLD"))
        Shrink(entity, growthComponent);
}

void GrowthSystem::Grow(std::shared_ptr<Entity> entity,
    std::shared_ptr<GrowthComponent> growthComponent)
{
    int level = growthComponent->GetLevel();

    level += 1;
    LOG_I("[GrowthSystem] Entity \"" << entity->GetId() << "\" has grown to "
        << "level " << level);

    growthComponent->SetEnergy(0);
    growthComponent->SetGrowthPower(0);
    growthComponent->SetLevel(level);
}

void GrowthSystem::Shrink(std::shared_ptr<Entity> entity,
    std::shared_ptr<GrowthComponent> growthComponent)
{
    int level = growthComponent->GetLevel();

    level -= 1;
    LOG_I("[GrowthSystem] Entity \"" << entity->GetId() << "\" has shrunk "
        << "to level " << level);

    growthComponent->SetEnergy(0);
    growthComponent->SetGrowthPower(0);
    growthComponent->SetLevel(level);
}

void GrowthSystem::SaturateLevel(std::shared_ptr<GrowthComponent> growthComponent)
{
    int level = growthComponent->GetLevel();
    int maxLevel = CFG_GETI("GROWTH_LEVEL_LIMIT");

    if (level > maxLevel)
        level = maxLevel;
    
    growthComponent->SetLevel(level);
}

bool GrowthSystem::KillSmallEntity(std::shared_ptr<Entity> entity,
    std::shared_ptr<GrowthComponent> growthComponent)
{
    if (growthComponent->GetLevel() <= 0)
    {
        Engine::GetInstance().DeleteEntity(entity);
        return true;
    }

    return false;
}

void GrowthSystem::UpdateCollisionRadius(
    std::shared_ptr<GrowthComponent> growthComponent,
    std::shared_ptr<ColliderComponent> colliderComponent)
{
    float radius = growthComponent->GetLevel()*colliderComponent->GetInitRadius();
    colliderComponent->SetRadius(radius);
}

void GrowthSystem::UpdateSpriteSize(std::shared_ptr<SpriteComponent> spriteComponent,
    std::shared_ptr<GrowthComponent> growthComponent)
{
    spriteComponent->SetScale(growthComponent->GetLevel()*spriteComponent->GetBaseScale());
}

void GrowthSystem::UpdateSpriteFrameDuration(std::shared_ptr<SpriteComponent> spriteComponent,
    std::shared_ptr<GrowthComponent> growthComponent)
{
    float growthPower = growthComponent->GetGrowthPower();
    float duration;

    if (growthPower > CFG_GETI("GROWTH_UPPER_THRESHOLD")/3)
        duration = 0.01;
    else if (growthPower < CFG_GETI("GROWTH_LOWER_THRESHOLD")/3)
        duration = 0.5;
    else
        duration = 0.1;

    spriteComponent->SetFrameDuration(duration);
}