// @file   Camera.h
// @author Matheus Vieira Portela
// @date   12/04/2015
//
// @brief Camera moves the screen by following a game object.

#ifndef CAMERA_H_
#define CAMERA_H_

#include "ConfigParser.h"
#include "GameObject.h"
#include "Point.h"
#include "Vector.h"

class Camera
{
  public:
    // Registers the object that the camera will follow.
    static void Follow(std::weak_ptr<GameObject> focus);

    // Stops following the registered object.
    static void Unfollow();

    // Gets focus object as shared pointer.
    static std::shared_ptr<GameObject> GetFocusObject();

    // Checks whether there is a object that the camera is following. This is
    // useful to check whether the object has been destroyed, for instance.
    static bool HasFocusObject();

    // Updates camera position with the registered object position.
    static void UpdatePositionByFocusObject();

    // Updates camera position by calculating displacement with camera speed.
    static void UpdatePositionBySpeed(float dt);

    // Updates camera position given a time interval.
    static void Update(float dt);

    // Converts a world point to screen coordinates.
    static Point WorldToScreenPoint(const Point& point);

    // Converts a screen point to world coordinates.
    static Point ScreenToWorldPoint(const Point& point);

    // Camera position (in pixels).
    static Point position;

    // Camera speed (in pixels/second).
    static Vector speed;
    
  private:
    // Current object that the camera follows. It must be a weak pointer to not
    // claim ownership of the object, since Camera is not a GameObject manager.
    static std::weak_ptr<GameObject> focus;
};

#endif // CAMERA_H_