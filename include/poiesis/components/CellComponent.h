// Stores whether the entity is a cell.

#ifndef CELL_COMPONENT_H_
#define CELL_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

class CellComponent : public Component
{
  public:
    CellComponent();
    std::string GetComponentClass();
};

#endif // CELL_COMPONENT_H_