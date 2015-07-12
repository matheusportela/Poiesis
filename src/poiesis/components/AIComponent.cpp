#include "poiesis/components/AIComponent.h"

AIComponent::AIComponent(std::string pursueComponent) :
    pursueComponent(pursueComponent)
{
}

std::string AIComponent::GetComponentClass()
{
    return "AIComponent";
}

std::string AIComponent::GetPursueComponent()
{
    return pursueComponent;
}

void AIComponent::SetPursueComponent(std::string pursueComponent)
{
    this->pursueComponent = pursueComponent;
}