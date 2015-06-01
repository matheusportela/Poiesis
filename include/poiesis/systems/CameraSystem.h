// Updates camera positioning.

#ifndef CAMERA_SYSTEM_H_
#define CAMERA_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/components/CameraComponent.h"
#include "poiesis/components/CameraFollowComponent.h"
#include "poiesis/components/ParticleComponent.h"

class CameraSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
};

#endif // CAMERA_SYSTEM_H_