// Stores whether the entity is infected with an anomaly.

#ifndef INFECTION_COMPONENT_H_
#define INFECTION_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

enum InfectionType
{
    NoInfection,
    CannotInput,
    Vulnerable,
    CannotEat,
    StrongImpulses
};

class InfectionComponent : public Component
{
  public:
    InfectionComponent(InfectionType infectionType, bool transmissible = true);
    std::string GetComponentClass();

    InfectionType GetInfectionType();
    void SetInfectionType(InfectionType infectionType);

    bool GetTransmissible();
    void SetTransmissible(bool transmissible);

  private:
    InfectionType infectionType;

    // Whether the entity can spread the infection to others.
    bool transmissible;
};

#endif // INFECTION_COMPONENT_H_