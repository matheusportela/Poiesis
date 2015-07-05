#include "poiesis/components/CameraComponent.h"

CameraComponent::CameraComponent(Vector position, float height) :
    position(position), height(height)
{
}

std::string CameraComponent::GetComponentClass()
{
    return "CameraComponent";
}

Vector CameraComponent::GetPosition()
{
    return position;
}

void CameraComponent::SetPosition(Vector position)
{
    this->position = position;
}

float CameraComponent::GetHeight()
{
    return height;
}

void CameraComponent::SetHeight(float height)
{
    this->height = height;
}