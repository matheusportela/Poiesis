// Creates food with time.

#ifndef AI_SYSTEM_H_
#define AI_SYSTEM_H_

#include <limits>

#include "bandit/Engine.h"

#include "poiesis/components/AIComponent.h"
#include "poiesis/components/EatableComponent.h"
#include "poiesis/components/ParticleComponent.h"

class AISystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
    Vector PursueComponent(std::shared_ptr<Entity> entity,
        std::string componentClass);
    Vector FleeFromComponent(std::shared_ptr<Entity> entity,
        std::string componentClass);
    Vector CalculateAttractionForce(Vector entityPosition,
        Vector attractionPosition);
    Vector CalculateRepulsionForce(Vector entityPosition,
        Vector repulsionPosition);
    Vector GetEntityPosition(std::shared_ptr<Entity> entity);
    std::shared_ptr<Entity> GetClosestEntity(
        std::shared_ptr<Entity> referenceEntity,
        std::vector<std::shared_ptr<Entity>> entities);

  private:
    float accumulatedTime;
};

#endif // AI_SYSTEM_H_