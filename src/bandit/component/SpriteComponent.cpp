#include "bandit/component/SpriteComponent.h"

SpriteComponent::SpriteComponent(std::string filename) :
    filename(filename)
{
}

std::string SpriteComponent::GetComponentClass()
{
    return "SpriteComponent";
}