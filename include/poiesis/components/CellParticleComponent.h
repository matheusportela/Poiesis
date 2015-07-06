// Stores whether the entity can compound a cell.

#ifndef CELL_PARTICLE_COMPONENT_H_
#define CELL_PARTICLE_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class CellParticleComponent : public Component
{
  public:
    CellParticleComponent();
    std::string GetComponentClass();
};

#endif // CELL_PARTICLE_COMPONENT_H_