// Process entities with animation components.

#ifndef ANIMATION_SYSTEM_H_
#define ANIMATION_SYSTEM_H_

#include <memory>
#include <string>

#include "bandit/Engine.h"

#include "poiesis/components/AnimationComponent.h"

class AnimationSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
};

#endif // ANIMATION_SYSTEM_H_