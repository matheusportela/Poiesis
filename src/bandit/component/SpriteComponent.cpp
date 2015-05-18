#include "bandit/component/SpriteComponent.h"

SpriteComponent::SpriteComponent(std::string filename) :
    filename(filename), x(0), y(0)
{
}

std::string SpriteComponent::GetComponentClass()
{
    return "SpriteComponent";
}