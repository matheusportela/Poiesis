#include "poiesis/systems/CollisionSystem.h"

std::string CollisionSystem::GetName()
{
    return "CollisionSystem";
}

void CollisionSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[CollisionSystem] Update: " << dt);

    auto entities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("ParticleComponent");
    std::shared_ptr<Entity> entity1;
    std::shared_ptr<Entity> entity2;

    for (unsigned int i = 0; i < entities.size() - 1; ++i)
    {
        for (unsigned int j = i + 1; j < entities.size(); ++j)
        {
            entity1 = entities[i];
            entity2 = entities[j];

            if (IsColliding(entity1, entity2))
            {
                LOG_D("[CollisionSystem] Colliding entities: " << entity1->GetId() << " and " << entity2->GetId());
            }
        }
    }
}

bool CollisionSystem::IsColliding(std::shared_ptr<Entity> entity1,
    std::shared_ptr<Entity> entity2)
{
    auto particleComponent1 = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity1, "ParticleComponent"));
    auto particleComponent2 = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity2, "ParticleComponent"));
    auto vector1 = particleComponent1->GetPosition();
    auto vector2 = particleComponent2->GetPosition();
    auto distance = vector1.CalculateDistance(vector2);

    LOG_D("Distance " << distance);
    if (distance < CFG_GETF("COLLISION_DISTANCE"))
        return true;
    return false;
}