// @file   PenguinsShootCommand.cpp
// @author Matheus Vieira Portela
// @date   08/05/2015
//
// @brief Make Penguins shoot in the direction where it's cannon is point to.

#include "PenguinsShootCommand.h"
#include "Penguins.h"

PenguinsShootCommand::PenguinsShootCommand(Penguins* penguins) :
    penguins(penguins)
{
}

void PenguinsShootCommand::Execute()
{
    LOG_D("[PenguinsShootCommand] Execute");
    penguins->Shoot();
}