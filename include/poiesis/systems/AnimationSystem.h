// Updates sprite frame, giving an illusion of animation.

#ifndef ANIMATION_SYSTEM_H_
#define ANIMATION_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/components/SpriteComponent.h"

class AnimationSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
};

#endif // ANIMATION_SYSTEM_H_