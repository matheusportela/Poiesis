#include "poiesis/components/ButtonComponent.h"

ButtonComponent::ButtonComponent(Rectangle rectangle,
    std::function<void()> callback) :
    rectangle(rectangle), callback(callback)
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

std::function<void()> ButtonComponent::GetCallback()
{
    return callback;
}

void ButtonComponent::SetCallback(std::function<void()> callback)
{
    this->callback = callback;
}