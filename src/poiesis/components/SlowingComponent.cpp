#include "poiesis/components/SlowingComponent.h"

SlowingComponent::SlowingComponent(float magnitude) :
    magnitude(magnitude)
{
}

std::string SlowingComponent::GetComponentClass()
{
    return "SlowingComponent";
}

float SlowingComponent::GetMagnitude()
{
    return magnitude;
}

void SlowingComponent::SetMagnitude(float magnitude)
{
    this->magnitude = magnitude;
}