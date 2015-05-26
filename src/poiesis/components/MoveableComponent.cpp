#include "poiesis/components/MoveableComponent.h"

MoveableComponent::MoveableComponent(bool active) :
    active(active)
{
}

std::string MoveableComponent::GetComponentClass()
{
    return "MoveableComponent";
}


float MoveableComponent::GetActive()
{
    return active;
}

void MoveableComponent::SetActive(float active)
{
    this->active = active;
}