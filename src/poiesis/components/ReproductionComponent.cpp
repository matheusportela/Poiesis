#include "poiesis/components/ReproductionComponent.h"

ReproductionComponent::ReproductionComponent(int type) :
    reproduced(false), type(type)
{
}

std::string ReproductionComponent::GetComponentClass()
{
    return "ReproductionComponent";
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