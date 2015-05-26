#include "poiesis/components/PositionComponent.h"

PositionComponent::PositionComponent(float x, float y) :
    x(x), y(y)
{
}

std::string PositionComponent::GetComponentClass()
{
    return "PositionComponent";
}