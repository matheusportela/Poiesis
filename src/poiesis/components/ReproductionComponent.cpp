#include "poiesis/components/ReproductionComponent.h"

ReproductionComponent::ReproductionComponent(int type) :
    enabled(false), reproduced(false), type(type)
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

bool ReproductionComponent::GetReproduced()
{
    return reproduced;
}

void ReproductionComponent::SetReproduced(bool reproduced)
{
    this->reproduced = reproduced;
}

int ReproductionComponent::GetType()
{
    return type;
}

void ReproductionComponent::SetType(int type)
{
    this->type = type;
}