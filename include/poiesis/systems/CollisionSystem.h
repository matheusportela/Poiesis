// Simulates body collision.

#ifndef COLLISION_SYSTEM_H_
#define COLLISION_SYSTEM_H_

#include <algorithm>

#include "bandit/Engine.h"

#include "poiesis/Quadtree.h"

#include "poiesis/components/CameraComponent.h"
#include "poiesis/components/ColliderComponent.h"
#include "poiesis/components/CombatComponent.h"
#include "poiesis/components/GrowthComponent.h"
#include "poiesis/components/ParticleComponent.h"
#include "poiesis/components/SlowingComponent.h"

class CollisionSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
    void CheckCollisions();
    bool IsColliding(std::shared_ptr<Entity> entity1,
        std::shared_ptr<Entity> entity2);
    void SolveCollision(std::shared_ptr<Entity> entity1,
        std::shared_ptr<Entity> entity2);
    void CollideBodies(std::shared_ptr<Entity> entity1,
        std::shared_ptr<Entity> entity2);
    void CombatEntities(std::shared_ptr<Entity> entity1,
        std::shared_ptr<Entity> entity2);
    void EatEntity(std::shared_ptr<Entity> eaterEntity,
        std::shared_ptr<Entity> eatableEntity);
    void SlowEntity(std::shared_ptr<Entity> slowingEntity,
        std::shared_ptr<Entity> movingEntity);

  private:
    std::vector<std::shared_ptr<Entity>> collidableEntities;
    std::vector<unsigned int> deletedEntities;
};

#endif // COLLISION_SYSTEM_H_