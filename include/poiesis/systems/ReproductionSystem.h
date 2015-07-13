#ifndef REPRODUCTION_SYSTEM_H_
#define REPRODUCTION_SYSTEM_H_

#include <memory>
#include <string>

#include "bandit/Engine.h"

#include "poiesis/components/GrowthComponent.h"
#include "poiesis/components/ReproductionComponent.h"
#include "poiesis/components/SpriteComponent.h"

class ReproductionSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
    void ConsumeEnergy(std::shared_ptr<GrowthComponent> growthComponent);

  private:
    Timer timer;
};

#endif // REPRODUCTION_SYSTEM_H_