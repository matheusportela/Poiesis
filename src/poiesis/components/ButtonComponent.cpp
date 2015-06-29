#include "poiesis/components/ButtonComponent.h"

ButtonComponent::ButtonComponent(Rectangle rectangle) : rectangle(rectangle)
{
}

std::string ButtonComponent::GetComponentClass()
{
    return "ButtonComponent";
}

Rectangle ButtonComponent::GetRectangle()
{
    return rectangle;
}

void ButtonComponent::SetRectangle(Rectangle rectangle)
{
    this->rectangle = rectangle;
}
