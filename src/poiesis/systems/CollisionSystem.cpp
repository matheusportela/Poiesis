#include "poiesis/systems/CollisionSystem.h"

std::string CollisionSystem::GetName()
{
    return "CollisionSystem";
}

void CollisionSystem::Update(float dt)
{
    // Avoid warnings for not using dt.
    LOG_D("[CollisionSystem] Update: " << dt);
    CheckCollisions();
}

void CollisionSystem::CheckCollisions()
{
    int initialLevel = 0;
    int maxLevels = 4;
    int maxObjects = 20;
    float maxDistance = 2000;
    Quadtree<std::shared_ptr<Entity>> quadtree(-2500, -2500, 5000, 5000,
        initialLevel, maxLevels, maxObjects);
    auto cameraEntities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("CameraComponent");
    collidableEntities = Engine::GetInstance().GetEntityManager()->GetAllEntitiesWithComponentOfClass("ColliderComponent");

    // Clear deleted entities from last iteration.
    deletedEntities.clear();

    std::shared_ptr<Entity> cameraEntity;
    if (cameraEntities.size() > 0)
        cameraEntity = cameraEntities[0];

    // Build quadtree for close enough entities.
    for (auto entity : collidableEntities)
    {
        auto particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "ParticleComponent"));
        auto position = particleComponent->GetPosition();

        // Ignore collision from things that aren't visible.
        if (cameraEntity)
        {
            auto cameraComponent = std::static_pointer_cast<CameraComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(cameraEntity, "CameraComponent"));
            auto cameraPosition = cameraComponent->GetPosition();

            if (cameraPosition.CalculateDistance(position) > maxDistance)
                continue;
            else
                quadtree.Add(entity, position.GetX(), position.GetY());
        }
        else
        {
            quadtree.Add(entity, position.GetX(), position.GetY());
        }
    }

    // Detect and solve collisions.
    for (unsigned int i = 0; i < collidableEntities.size(); ++i)
    {
        auto entity = collidableEntities[i];

        auto particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity, "ParticleComponent"));
        auto position = particleComponent->GetPosition();
        auto quadtreeEntities = quadtree.Get(position.GetX(), position.GetY());

        for (unsigned int j = 0; j < quadtreeEntities.size(); ++j)
        {
            auto otherEntity = quadtreeEntities[j];

            LOG_D("Analysing collision between " << entity->GetId() << " and " << otherEntity->GetId());

            if (std::find(deletedEntities.begin(), deletedEntities.end(),  entity->GetId()) != deletedEntities.end())
            {
                LOG_D("Ignoring deleted entity: " << entity->GetId());
                continue;
            }

            if (std::find(deletedEntities.begin(), deletedEntities.end(),  otherEntity->GetId()) != deletedEntities.end())
            {
                LOG_D("Ignoring deleted entity: " << otherEntity->GetId());
                continue;
            }

            if (entity->GetId() != otherEntity->GetId()
                && IsColliding(entity, otherEntity))
                SolveCollision(entity, otherEntity);
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
    if (Engine::GetInstance().GetEntityManager()->HasComponent(entity1, "GrowthComponent") && 
        Engine::GetInstance().GetEntityManager()->HasComponent(entity2, "EatableComponent"))
        EatEntity(entity1, entity2);
    else if (Engine::GetInstance().GetEntityManager()->HasComponent(entity2, "GrowthComponent") && 
        Engine::GetInstance().GetEntityManager()->HasComponent(entity1, "EatableComponent"))
        EatEntity(entity2, entity1);
    else if (Engine::GetInstance().GetEntityManager()->HasComponent(entity1, "CombatComponent") && 
        Engine::GetInstance().GetEntityManager()->HasComponent(entity2, "CombatComponent"))
        CombatEntities(entity1, entity2);
    else if (Engine::GetInstance().GetEntityManager()->HasComponent(entity1, "SlowingComponent") && 
        Engine::GetInstance().GetEntityManager()->HasComponent(entity2, "ParticleComponent"))
        SlowEntity(entity1, entity2);
    else if (Engine::GetInstance().GetEntityManager()->HasComponent(entity2, "SlowingComponent") && 
        Engine::GetInstance().GetEntityManager()->HasComponent(entity1, "ParticleComponent"))
        SlowEntity(entity2, entity1);
    else
        CollideBodies(entity1, entity2);
}

void CollisionSystem::CollideBodies(std::shared_ptr<Entity> entity1,
    std::shared_ptr<Entity> entity2)
{
    LOG_D("[CollisionSystem] Colliding entities: " << entity1->GetId() << " and " << entity2->GetId());

    auto particleComponent1 = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity1, "ParticleComponent"));
    auto particleComponent2 = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity2, "ParticleComponent"));
    auto colliderComponent1 = std::static_pointer_cast<ColliderComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity1, "ColliderComponent"));
    auto colliderComponent2 = std::static_pointer_cast<ColliderComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity2, "ColliderComponent"));
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

void CollisionSystem::CombatEntities(std::shared_ptr<Entity> entity1,
        std::shared_ptr<Entity> entity2)
{
    auto combatComponent1 = std::static_pointer_cast<CombatComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity1, "CombatComponent"));
    auto combatComponent2 = std::static_pointer_cast<CombatComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(entity2, "CombatComponent"));

    int power1 = combatComponent1->GetPower();
    int power2 = combatComponent2->GetPower();

    LOG_W("[CollisionSystem] Combat between entity " << entity1->GetId()
        << " and " << entity2->GetId());

    if (power1 > power2)
    {
        LOG_W("[CollisionSystem] Entity " << entity1->GetId()
            << " wins the combat");
        EatEntity(entity1, entity2);
    }
    else if (power2 > power1)
    {
        LOG_W("[CollisionSystem] Entity " << entity2->GetId()
            << " wins the combat");
        EatEntity(entity2, entity1);
    }
    else
    {
        LOG_W("[CollisionSystem] Tied combat");
        CollideBodies(entity1, entity2);
    }
}

void CollisionSystem::EatEntity(std::shared_ptr<Entity> eaterEntity,
    std::shared_ptr<Entity> eatableEntity)
{
    LOG_D("[CollisionSystem] Entity " << eaterEntity->GetId() << " is eating entity " << eatableEntity->GetId());

    auto growthComponent = std::static_pointer_cast<GrowthComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(eaterEntity, "GrowthComponent"));
    auto energy = growthComponent->GetEnergy();
    ++energy;
    growthComponent->SetEnergy(energy);

    // Delete food entity.
    Engine::GetInstance().GetEntityManager()->DeleteEntity(eatableEntity);

    for (unsigned int i = 0; i < collidableEntities.size(); ++i)
    {
        auto entity = collidableEntities[i];

        if (entity->GetId() == eatableEntity->GetId())
        {
            collidableEntities.erase(collidableEntities.begin() + i);
            --i;
        }
    }

    // Delete also from the entities to be collided.
    deletedEntities.push_back(eatableEntity->GetId());
}

void CollisionSystem::SlowEntity(std::shared_ptr<Entity> slowingEntity,
    std::shared_ptr<Entity> movingEntity)
{
    auto slowingComponent = std::static_pointer_cast<SlowingComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(slowingEntity, "SlowingComponent"));
    auto particleComponent = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetEntityManager()->GetSingleComponentOfClass(movingEntity, "ParticleComponent"));

    float magnitude = slowingComponent->GetMagnitude();
    Vector velocity = particleComponent->GetVelocity();

    velocity *= magnitude;

    particleComponent->SetVelocity(velocity);
}