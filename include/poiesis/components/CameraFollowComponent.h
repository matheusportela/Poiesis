// Stores data relevant for collision between entities.

#ifndef CAMERA_FOLLOW_COMPONENT_H_
#define CAMERA_FOLLOW_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class CameraFollowComponent : public Component
{
  public:
    CameraFollowComponent(bool enabled = true);
    std::string GetComponentClass();

    bool GetEnabled();
    void SetEnabled(bool enabled);

  private:
    // Holds whether the entity must be followed by the camera.
    bool enabled;
};

#endif // CAMERA_FOLLOW_COMPONENT_H_