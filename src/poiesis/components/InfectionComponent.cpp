#include "poiesis/components/InfectionComponent.h"

InfectionComponent::InfectionComponent(InfectionType infectionType,
    bool transmissible, bool temporary, float remainingTime) :
    infectionType(infectionType), transmissible(transmissible),
    temporary(temporary), remainingTime(remainingTime)
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

bool InfectionComponent::GetTemporary()
{
    return temporary;
}

void InfectionComponent::SetTemporary(bool temporary)
{
    this->temporary = temporary;
}

float InfectionComponent::GetRemainingTime()
{
    return remainingTime;
}

void InfectionComponent::SetRemainingTime(float remainingTime)
{
    this->remainingTime = remainingTime;
}