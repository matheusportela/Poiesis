// @file   PenguinsSlowDownCommand.cpp
// @author Matheus Vieira Portela
// @date   08/05/2015
//
// @brief Make Penguins go slower.

#include "PenguinsSlowDownCommand.h"
#include "Penguins.h"

PenguinsSlowDownCommand::PenguinsSlowDownCommand(Penguins* penguins) :
    penguins(penguins)
{
}

void PenguinsSlowDownCommand::Execute()
{
    LOG_D("[PenguinsSlowDownCommand] Execute");
    penguins->SlowDownCallback();
}