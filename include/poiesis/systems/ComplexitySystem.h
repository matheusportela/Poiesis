// Grows entities with time.

#ifndef COMPLEXITY_SYSTEM_H_
#define COMPLEXITY_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"

#include "poiesis/components/ComplexityComponent.h"
#include "poiesis/components/GrowthComponent.h"
#include "poiesis/components/ParticleComponent.h"
#include "poiesis/components/SpriteComponent.h"

class ComplexitySystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
    void ConsumeEnergy(std::shared_ptr<GrowthComponent> growthComponent);
    void AdjustComplexityParticleDistance(std::shared_ptr<Entity> entity,
        std::shared_ptr<GrowthComponent> growthComponent);
    bool KillEntityWithoutEnergy(std::shared_ptr<Entity> entity,
        std::shared_ptr<GrowthComponent> growthComponent);
    void EmitParticle(std::shared_ptr<Entity> entity);

  private:
    Timer timer;
};

#endif // COMPLEXITY_SYSTEM_H_