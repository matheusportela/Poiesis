// Simulates body collision.

#ifndef COLLISION_SYSTEM_H_
#define COLLISION_SYSTEM_H_

#include <algorithm>

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"
#include "poiesis/Quadtree.h"

#include "poiesis/components/CameraComponent.h"
#include "poiesis/components/ColliderComponent.h"
#include "poiesis/components/CombatComponent.h"
#include "poiesis/components/ComplexityComponent.h"
#include "poiesis/components/GrowthComponent.h"
#include "poiesis/components/ParticleComponent.h"
#include "poiesis/components/ReproductionComponent.h"
#include "poiesis/components/SlowingComponent.h"
#include "poiesis/components/SpriteComponent.h"
#include "poiesis/components/VitaminComponent.h"

class CollisionSystem : public System
{
  public:
    CollisionSystem();
    std::string GetName();
    void EnableReproduction();
    void DisableReproduction();
    void EnableComplexity();
    void DisableComplexity();
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
    bool ReproduceEntities(std::shared_ptr<Entity> entity1,
        std::shared_ptr<Entity> entity2);
    void IncorporateEntity(std::shared_ptr<Entity> eaterEntity,
        std::shared_ptr<Entity> eatableEntity);
    void EatEntity(std::shared_ptr<Entity> eaterEntity,
        std::shared_ptr<Entity> eatableEntity);
    void DestroyEntity(std::shared_ptr<Entity> entity);
    void SlowEntity(std::shared_ptr<Entity> slowingEntity,
        std::shared_ptr<Entity> movingEntity);
    void VitaminateEntity(std::shared_ptr<Entity> vitamineEntity,
        std::shared_ptr<Entity> growingEntity);
    void EmitParticles(std::shared_ptr<Entity> entity);

  private:
    bool reproductionEnabled;
    bool complexityEnabled;
    std::vector<std::shared_ptr<Entity>> collidableEntities;
    std::vector<unsigned int> deletedEntities;
};

#endif // COLLISION_SYSTEM_H_