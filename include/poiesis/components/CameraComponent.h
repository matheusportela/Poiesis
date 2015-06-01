// Stores data relevant for collision between entities.

#ifndef CAMERA_COMPONENT_H_
#define CAMERA_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class CameraComponent : public Component
{
  public:
    CameraComponent(Vector position = Vector(0, 0));
    std::string GetComponentClass();

    Vector GetPosition();
    void SetPosition(Vector position);

  private:
    // Holds the camera center point in 2D.
    Vector position;
};

#endif // CAMERA_COMPONENT_H_