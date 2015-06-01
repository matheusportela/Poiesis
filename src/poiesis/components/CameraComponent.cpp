#include "poiesis/components/CameraComponent.h"

CameraComponent::CameraComponent(Vector position) :
    position(position)
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