#include "poiesis/components/SlowerComponent.h"

SlowerComponent::SlowerComponent(float magnitude) :
    magnitude(magnitude)
{
}

std::string SlowerComponent::GetComponentClass()
{
    return "SlowerComponent";
}

float SlowerComponent::GetMagnitude()
{
    return magnitude;
}

void SlowerComponent::SetMagnitude(float magnitude)
{
    this->magnitude = magnitude;
}