#include "poiesis/systems/AISystem.h"

std::string AISystem::GetName()
{
    return "AISystem";
}

void AISystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[AISystem] Update: " << dt);

    auto aiEntities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("AIComponent");
    auto eatableEntities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("EatableComponent");

    if (aiEntities.size() == 0 || eatableEntities.size() == 0)
        return;

    std::shared_ptr<ParticleComponent> aiParticleComponent;
    std::shared_ptr<ParticleComponent> eatableParticleComponent;
    float distance;
    float closestDistance = std::numeric_limits<float>::max();
    Vector aiParticlePosition;
    Vector eatableParticlePosition;
    std::shared_ptr<Entity> closestEatableEntity;
    Vector closestPosition;
    Vector inputForce;
    Vector resultantForce;

    for (auto aiEntity : aiEntities)
    {
        aiParticleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(aiEntity, "ParticleComponent"));
        aiParticlePosition = aiParticleComponent->GetPosition();

        for (auto eatableEntity : eatableEntities)
        {
            eatableParticleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(eatableEntity, "ParticleComponent"));
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
        inputForce *= CFG_GETF("AI_DRIVING_FORCE")/(1 + distance); // Summing with 1 to avoid division by zero.
        resultantForce = inputForce + aiParticleComponent->GetForce();
        aiParticleComponent->SetForce(resultantForce);
    }
}