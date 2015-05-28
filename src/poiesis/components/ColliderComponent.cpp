#include "poiesis/components/ColliderComponent.h"

ColliderComponent::ColliderComponent(float radius) :
    radius(radius)
{
}

std::string ColliderComponent::GetComponentClass()
{
    return "ColliderComponent";
}

float ColliderComponent::GetRadius()
{
    return radius;
}

void ColliderComponent::SetRadius(float radius)
{
    this->radius = radius;
}