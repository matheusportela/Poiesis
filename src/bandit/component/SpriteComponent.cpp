#include "bandit/component/SpriteComponent.h"

SpriteComponent::SpriteComponent(std::string filename, int x, int y) :
    filename(filename), x(x), y(y)
{
}

std::string SpriteComponent::GetComponentClass()
{
    return "SpriteComponent";
}