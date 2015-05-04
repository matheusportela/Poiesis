// @file   Camera.cpp
// @author Matheus Vieira Portela
// @date   12/04/2015
//
// @brief Camera moves the screen by following a game object.

#include "Camera.h"

Point Camera::position;
Vector Camera::speed;
GameObject* Camera::focus = NULL;

void Camera::Follow(GameObject* focus)
{
    Camera::focus = focus;
}

void Camera::Unfollow()
{
    Camera::focus = NULL;
}

void Camera::UpdatePositionByFocusObject()
{
    position = Camera::focus->GetCenter();
}

void Camera::UpdatePositionBySpeed(float dt)
{
    Vector displacement = Camera::speed;

    // X = X0 + V*dt
    displacement.Multiply(dt);
    Camera::position.Add(displacement);
}

void Camera::Update(float dt)
{
    if (Camera::focus)
        UpdatePositionByFocusObject();
    else
        UpdatePositionBySpeed(dt);
}

Point Camera::WorldToScreenPoint(const Point& point)
{
    Point convertedPoint = point;
    convertedPoint.Subtract(Camera::position);
    return convertedPoint;
}

Point Camera::ScreenToWorldPoint(const Point& point)
{
    Point convertedPoint = point;
    convertedPoint.Add(Camera::position);
    return convertedPoint;
}