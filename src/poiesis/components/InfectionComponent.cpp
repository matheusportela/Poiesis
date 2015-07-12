#include "poiesis/components/InfectionComponent.h"

InfectionComponent::InfectionComponent(InfectionType infectionType,
    bool transmissible) :
    infectionType(infectionType), transmissible(transmissible)
{
}

std::string InfectionComponent::GetComponentClass()
{
    return "InfectionComponent";
}

InfectionType InfectionComponent::GetInfectionType()
{
    return infectionType;
}

void InfectionComponent::SetInfectionType(InfectionType infectionType)
{
    this->infectionType = infectionType;
}

bool InfectionComponent::GetTransmissible()
{
    return transmissible;
}

void InfectionComponent::SetTransmissible(bool transmissible)
{
    this->transmissible = transmissible;
}