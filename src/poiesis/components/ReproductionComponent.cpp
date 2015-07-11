#include "poiesis/components/ReproductionComponent.h"

ReproductionComponent::ReproductionComponent(int type) :
    enabled(true), type(type)
{
}

std::string ReproductionComponent::GetComponentClass()
{
    return "ReproductionComponent";
}

bool ReproductionComponent::GetEnabled()
{
    return enabled;
}

void ReproductionComponent::SetEnabled(bool enabled)
{
    this->enabled = enabled;
}

int ReproductionComponent::GetType()
{
    return type;
}

void ReproductionComponent::SetType(int type)
{
    this->type = type;
}