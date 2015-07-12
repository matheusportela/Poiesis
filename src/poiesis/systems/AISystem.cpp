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
    std::shared_ptr<ParticleComponent> eatableParticleComponent;
    std::vector<std::shared_ptr<Entity>> pursueEntities;
    float distance;
    float closestDistance = std::numeric_limits<float>::max();
    Vector aiParticlePosition;
    Vector eatableParticlePosition;
    std::shared_ptr<Entity> closestEatableEntity;
    Vector closestPosition;
    Vector inputForce;
    Vector resultantForce;
    Random r;

    for (auto entity : entities)
    {
        aiComponent = std::static_pointer_cast<AIComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "AIComponent"));
        aiParticleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity, "ParticleComponent"));
        aiParticlePosition = aiParticleComponent->GetPosition();
        pursueEntities = Engine::GetInstance().GetAllEntitiesWithComponentOfClass(aiComponent->GetPursueComponent());

        if (pursueEntities.size() == 0)
            continue;

        for (auto eatableEntity : pursueEntities)
        {
            eatableParticleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetSingleComponentOfClass(eatableEntity, "ParticleComponent"));
            eatableParticlePosition = eatableParticleComponent->GetPosition();

            distance = eatableParticlePosition.CalculateDistance(aiParticlePosition);

            if (distance < closestDistance)
            {
                closestEatableEntity = eatableEntity;
                closestDistance = distance;
                closestPosition = eatableParticlePosition;
            }
        }

        inputForce = closestPosition - aiParticlePosition;
        inputForce.Normalize();
        inputForce *= r.GenerateFloat(CFG_GETF("AI_MIN_DRIVING_FORCE"), CFG_GETF("AI_MAX_DRIVING_FORCE"));
        resultantForce = inputForce + aiParticleComponent->GetForce();
        aiParticleComponent->SetForce(resultantForce);
    }
}