// Grows entities with time.

#ifndef GROWTH_SYSTEM_H_
#define GROWTH_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/components/ColliderComponent.h"
#include "poiesis/components/GrowthComponent.h"
#include "poiesis/components/SpriteComponent.h"

class GrowthSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
    void ConsumeEnergy(std::shared_ptr<GrowthComponent> growthComponent);
    void UpdateGrowthPower(std::shared_ptr<GrowthComponent> growthComponent);
    void GrowOrShrink(std::shared_ptr<Entity> entity,
        std::shared_ptr<GrowthComponent> growthComponent);
    void Grow(std::shared_ptr<Entity> entity,
        std::shared_ptr<GrowthComponent> growthComponent);
    void Shrink(std::shared_ptr<Entity> entity,
        std::shared_ptr<GrowthComponent> growthComponent);
    void SaturateLevel(std::shared_ptr<GrowthComponent> growthComponent); // This should be moved to Math
    bool KillSmallEntity(std::shared_ptr<Entity> entity,
        std::shared_ptr<GrowthComponent> growthComponent);
    void UpdateCollisionRadius(
        std::shared_ptr<GrowthComponent> growthComponent,
        std::shared_ptr<ColliderComponent> colliderComponent);

  private:
    Timer timer;
};

#endif // GROWTH_SYSTEM_H_