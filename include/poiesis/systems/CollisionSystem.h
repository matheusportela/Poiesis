// Simulates body collision.

#ifndef COLLISION_SYSTEM_H_
#define COLLISION_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/components/ColliderComponent.h"
#include "poiesis/components/GrowthComponent.h"
#include "poiesis/components/ParticleComponent.h"

class CollisionSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
    bool IsColliding(std::shared_ptr<Entity> entity1,
        std::shared_ptr<Entity> entity2);
    void SolveCollision(std::shared_ptr<Entity> entity1,
        std::shared_ptr<Entity> entity2);
    void CollideBodies(std::shared_ptr<Entity> entity1,
        std::shared_ptr<Entity> entity2);
    void EatEntity(std::shared_ptr<Entity> eaterEntity,
        std::shared_ptr<Entity> eatableEntity);

  private:
    std::vector<std::shared_ptr<Entity>> collidableEntities;
};

#endif // COLLISION_SYSTEM_H_