// Stores data relevant for collision between entities.

#ifndef CAMERA_COMPONENT_H_
#define CAMERA_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class CameraComponent : public Component
{
  public:
    CameraComponent(Vector position = Vector(0, 0), float height = 1);
    std::string GetComponentClass();

    Vector GetPosition();
    void SetPosition(Vector position);

    float GetHeight();
    void SetHeight(float height);

  private:
    // Holds the camera center point in 2D.
    Vector position;

    // Holds the camera height from the game's 2D plane.
    float height;
};

#endif // CAMERA_COMPONENT_H_