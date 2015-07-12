#include "poiesis/systems/AISystem.h"

std::string AISystem::GetName()
{
    return "AISystem";
}

void AISystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[AISystem] Update: " << dt);

    auto entities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass("AIComponent");

    if (entities.size() == 0)
        return;

    std::shared_ptr<AIComponent> aiComponent;
    std::shared_ptr<ParticleComponent> aiParticleComponent;
    std::vector<std::shared_ptr<Entity>> pursueEntities;
    Vector aiParticlePosition;
    Vector resultantForce;
    Vector drivingForce;

    for (auto entity : entities)
    {
        aiComponent = std::static_pointer_cast<AIComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "AIComponent"));
        
        drivingForce += PursueComponent(entity, aiComponent->GetPursueComponent());
        
        if (aiComponent->GetPursueComponent() == "CellParticleComponent")
            drivingForce += FleeFromComponent(entity, "ComplexityComponent");

        auto aiParticleComponent = std::static_pointer_cast<ParticleComponent>(
            Engine::GetInstance().GetSingleComponentOfClass(entity, "ParticleComponent"));

        resultantForce = aiParticleComponent->GetForce() + drivingForce;
        aiParticleComponent->SetForce(resultantForce);
    }
}

Vector AISystem::PursueComponent(std::shared_ptr<Entity> entity,
    std::string componentClass)
{
    auto aiParticlePosition = GetEntityPosition(entity);
    auto pursueEntities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass(componentClass);
    auto closestEntity = GetClosestEntity(entity, pursueEntities);

    if (!closestEntity)
        return Vector(0, 0);

    auto closestParticlePosition = GetEntityPosition(closestEntity);
    auto drivingForce = CalculateAttractionForce(aiParticlePosition, closestParticlePosition);
    return drivingForce;
}

Vector AISystem::FleeFromComponent(std::shared_ptr<Entity> entity,
    std::string componentClass)
{
    auto aiParticlePosition = GetEntityPosition(entity);
    auto pursueEntities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass(componentClass);
    auto closestEntity = GetClosestEntity(entity, pursueEntities);

    if (!closestEntity)
        return Vector(0, 0);

    auto closestParticlePosition = GetEntityPosition(closestEntity);
    auto drivingForce = CalculateRepulsionForce(aiParticlePosition, closestParticlePosition)
        *(1/(1 + aiParticlePosition.CalculateDistance(closestParticlePosition)));
    return drivingForce;
}

Vector AISystem::CalculateAttractionForce(Vector entityPosition,
    Vector attractionPosition)
{
    Random r;
    Vector force = attractionPosition - entityPosition;
    force.Normalize();
    force *= r.GenerateFloat(CFG_GETF("AI_MIN_DRIVING_FORCE"), CFG_GETF("AI_MAX_DRIVING_FORCE"));
    return force;
}

Vector AISystem::CalculateRepulsionForce(Vector entityPosition,
    Vector repulsionPosition)
{
    Vector force = CalculateAttractionForce(entityPosition, repulsionPosition);
    return (force*(-1));
}

Vector AISystem::GetEntityPosition(std::shared_ptr<Entity> entity)
{
    auto particleComponent = std::static_pointer_cast<ParticleComponent>(
            Engine::GetInstance().GetSingleComponentOfClass(entity, "ParticleComponent"));
    return particleComponent->GetPosition();
}

std::shared_ptr<Entity> AISystem::GetClosestEntity(
    std::shared_ptr<Entity> referenceEntity,
    std::vector<std::shared_ptr<Entity>> entities)
{
    std::shared_ptr<Entity> closestEntity;
    Vector position = GetEntityPosition(referenceEntity);
    float closestDistance = std::numeric_limits<float>::max();
    
    for (auto entity : entities)
    {
        auto particlePosition = GetEntityPosition(entity);
        auto distance = particlePosition.CalculateDistance(position);

        if (distance < closestDistance && referenceEntity->GetId() != entity->GetId())
        {
            closestEntity = entity;
            closestDistance = distance;
        }
    }

    return closestEntity;
}