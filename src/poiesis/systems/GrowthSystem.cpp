#include "poiesis/systems/GrowthSystem.h"

std::string GrowthSystem::GetName()
{
    return "GrowthSystem";
}

void GrowthSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[GrowthSystem] Update: " << dt);

    std::shared_ptr<GrowthComponent> growthComponent;
    std::shared_ptr<SpriteComponent> spriteComponent;
    std::shared_ptr<ColliderComponent> colliderComponent;
    auto entities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("GrowthComponent");

    timer.Update(dt);

    for (auto entity : entities)
    {
        // Load entity's data
        growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "GrowthComponent"));
        colliderComponent = std::static_pointer_cast<ColliderComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "ColliderComponent"));

        // Execute growth logic
        ConsumeEnergy(growthComponent);
        UpdateGrowthPower(growthComponent);
        GrowOrShrink(entity, growthComponent);
        SaturateLevel(growthComponent);

        if (KillSmallEntity(entity, growthComponent))
            continue;

        CalculateCollisionRadius(growthComponent, colliderComponent);

        // Save entity's data
        for (auto component : Engine::GetInstance().GetEntityManager()->GetComponentsOfClass(entity, "SpriteComponent"))
        {
            spriteComponent = std::static_pointer_cast<SpriteComponent>(component);
            spriteComponent->SetScale(growthComponent->GetLevel());
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
    int energy = growthComponent->GetEnergy();
    int growthPower = growthComponent->GetGrowthPower();
    int growthAmount = 1;
    int growthSpeed;

    if (energy <= -2)
        growthSpeed = -2;
    else if (energy == -1)
        growthSpeed = -1;
    else if (energy == 0)
        growthSpeed = 0;
    else if (energy == 1)
        growthSpeed = 1;
    else if (energy >= 2)
        growthSpeed = 2;

    growthPower += growthAmount*growthSpeed;

    growthComponent->SetGrowthPower(growthPower);
}

void GrowthSystem::GrowOrShrink(std::shared_ptr<Entity> entity,
    std::shared_ptr<GrowthComponent> growthComponent)
{
    int energy = growthComponent->GetEnergy();

    if (energy >= CFG_GETI("GROWTH_UPPER_THRESHOLD"))
        Grow(entity, growthComponent);
    else if (energy <= CFG_GETI("GROWTH_LOWER_THRESHOLD"))
        Shrink(entity, growthComponent);
}

void GrowthSystem::Grow(std::shared_ptr<Entity> entity,
    std::shared_ptr<GrowthComponent> growthComponent)
{
    int energy = growthComponent->GetEnergy();
    int level = growthComponent->GetLevel();

    energy = 0;
    level += 1;
    LOG_I("[GrowthSystem] Entity \"" << entity->GetId() << "\" has grown to "
        << "level " << level);

    growthComponent->SetEnergy(energy);
    growthComponent->SetLevel(level);
}

void GrowthSystem::Shrink(std::shared_ptr<Entity> entity,
    std::shared_ptr<GrowthComponent> growthComponent)
{
    int energy = growthComponent->GetEnergy();
    int level = growthComponent->GetLevel();

    energy = 0;
    level -= 1;
    LOG_I("[GrowthSystem] Entity \"" << entity->GetId() << "\" has shrunk "
        << "to level " << level);

    growthComponent->SetEnergy(energy);
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
        Engine::GetInstance().GetEntityManager()->DeleteEntity(entity);
        return true;
    }

    return false;
}

void GrowthSystem::CalculateCollisionRadius(
    std::shared_ptr<GrowthComponent> growthComponent,
    std::shared_ptr<ColliderComponent> colliderComponent)
{
    float radius = growthComponent->GetLevel()*colliderComponent->GetInitRadius();
    colliderComponent->SetRadius(radius);
}