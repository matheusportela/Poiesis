#include "poiesis/components/PositionComponent.h"

PositionComponent::PositionComponent(float x, float y, bool movable) :
    x(x), y(y), movable(movable)
{
}

std::string PositionComponent::GetComponentClass()
{
    return "PositionComponent";
}