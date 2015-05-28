#include "poiesis/systems/CollisionSystem.h"

std::string CollisionSystem::GetName()
{
    return "CollisionSystem";
}

void CollisionSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[CollisionSystem] Update: " << dt);

    auto entities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("ColliderComponent");
    std::shared_ptr<Entity> entity1;
    std::shared_ptr<Entity> entity2;

    // This collision detection is a shame: O(n^2) complexity!
    for (unsigned int i = 0; i < entities.size() - 1; ++i)
    {
        for (unsigned int j = i + 1; j < entities.size(); ++j)
        {
            entity1 = entities[i];
            entity2 = entities[j];

            if (IsColliding(entity1, entity2))
            {
                LOG_D("[CollisionSystem] Colliding entities: " << entity1->GetId() << " and " << entity2->GetId());
                SolveCollision(entity1, entity2);
            }
        }
    }
}

bool CollisionSystem::IsColliding(std::shared_ptr<Entity> entity1,
    std::shared_ptr<Entity> entity2)
{
    auto colliderComponent1 = std::static_pointer_cast<ColliderComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity1, "ColliderComponent"));
    auto colliderComponent2 = std::static_pointer_cast<ColliderComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity2, "ColliderComponent"));
    auto particleComponent1 = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity1, "ParticleComponent"));
    auto particleComponent2 = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity2, "ParticleComponent"));
    float radius1 = colliderComponent1->GetRadius();
    float radius2 = colliderComponent2->GetRadius();
    Vector position1 = particleComponent1->GetPosition();
    Vector position2 = particleComponent2->GetPosition();
    float distance = position1.CalculateDistance(position2);

    if (distance < (radius1 + radius2))
        return true;
    return false;
}

void CollisionSystem::SolveCollision(std::shared_ptr<Entity> entity1,
    std::shared_ptr<Entity> entity2)
{
    auto colliderComponent1 = std::static_pointer_cast<ColliderComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity1, "ColliderComponent"));
    auto colliderComponent2 = std::static_pointer_cast<ColliderComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity2, "ColliderComponent"));
    auto particleComponent1 = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity1, "ParticleComponent"));
    auto particleComponent2 = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity2, "ParticleComponent"));
    float radius1 = colliderComponent1->GetRadius();
    float radius2 = colliderComponent2->GetRadius();
    Vector position1 = particleComponent1->GetPosition();
    Vector position2 = particleComponent2->GetPosition();
    float distance = position1.CalculateDistance(position2);
    float difference = radius1 + radius2 - distance;

    Vector direction = position2 - position1;
    direction.Normalize();

    // Applying force contrary to the collision direction. This force should
    // depend on the energy of the collision
    float forceMag = 100;
    Vector force1 = direction*(-forceMag);
    Vector force2 = direction*(forceMag);

    particleComponent1->SetForce(force1);
    particleComponent2->SetForce(force2);
    
    // Avoiding overlapping
    position1 += direction*(-difference/2);
    position2 += direction*(difference/2);

    particleComponent1->SetPosition(position1);
    particleComponent2->SetPosition(position2);
}